from sqlalchemy.orm import declarative_base
from sqlalchemy import Column, Integer, String

Base = declarative_base()

class Student(Base):
    __tablename__ = "students"
    id = Column(Integer,primary_key=True)
    name = Column(String)
    age = Column(Integer)
    department = Column(String)
    email = Column(String)
