
from fastapi import FastAPI, Depends
from pydantic import BaseModel
from typing import List

from database import SessionLocal,engine,get_db
from model import Base
import model

from fastapi.middleware.cors import CORSMiddleware

model.Base.metadata.create_all(bind=engine)

app = FastAPI()
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

class Student(BaseModel):
    id : int
    name : str
    age : int
    department : str
    email : str

students : List[Student] = []


@app.get("/")
def root_read():
    return {"Message" : "Welcome to student Management System"}

@app.get("/students")
def get_students(db = Depends(get_db)):
    #query
    students = db.query(model.Student).all()
    return students

@app.post("/students")
def add_student(new_student : Student,db = Depends (get_db)):
    student = model.Student(
    id=new_student.id,
    name=new_student.name,
    age=new_student.age,
    department=new_student.department,
    email=new_student.email
)

    for existing_student in students:
        if existing_student.id == new_student.id:
            return {"Error":"No Duplicate Values are allowed"}
    
    db.add(student)
    db.commit()
    db.refresh(student)
    return student

@app.put("/students/{student_id}")
def update_student(student_id : int ,updated_student : Student,db = Depends(get_db)):
    db_student = db.query(model.Student).filter(model.Student.id == student_id).first()
    if db_student is None:
        return {"error" : "Student not found"}
    
    db_student.name = updated_student.name
    db_student.age = updated_student.age
    db_student.department = updated_student.department
    db_student.email = updated_student.email
    db.commit()
    db.refresh(db_student)
    return db_student
    

@app.delete("/students/{student_id}")
def delete_student(student_id : int,db = Depends(get_db)):
    db_student = db.query(model.Student).filter(model.Student.id == student_id).first()

    if db_student is None :
        return {"error" : "Student not found"}
    
    db.delete(db_student)
    db.commit()

    return {"message" : "Student deleted successfully"}

