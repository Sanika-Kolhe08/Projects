const API="http://127.0.0.1:8000/students";

window.onload=loadStudents;

function loadStudents(){

fetch(API)

.then(response=>response.json())

.then(data=>{

const table=document.getElementById("studentTable");

table.innerHTML="";

data.forEach(student=>{

table.innerHTML+=`

<tr>

<td>${student.id}</td>

<td>${student.name}</td>

<td>${student.age}</td>

<td>${student.department}</td>

<td>${student.email}</td>

<td><button class="edit" onclick="editStudent(${student.id})">Edit</button></td>

<td><button class="delete" onclick="deleteStudent(${student.id})">Delete</button></td>

</tr>

`;

});

});

}

function addStudent(){

const student={

id:parseInt(document.getElementById("id").value),

name:document.getElementById("name").value,

age:parseInt(document.getElementById("age").value),

department:document.getElementById("department").value,

email:document.getElementById("email").value

};

fetch(API,{

method:"POST",

headers:{

"Content-Type":"application/json"

},

body:JSON.stringify(student)

})

.then(()=>{

loadStudents();

document.querySelectorAll("input").forEach(input=>input.value="");

});

}

function deleteStudent(id){

fetch(API+"/"+id,{

method:"DELETE"

})

.then(()=>loadStudents());

}

function editStudent(id){

const name=prompt("Enter New Name");

const age=prompt("Enter New Age");

const department=prompt("Enter Department");

const email=prompt("Enter Email");

fetch(API+"/"+id,{

method:"PUT",

headers:{

"Content-Type":"application/json"

},

body:JSON.stringify({

id:id,

name:name,

age:parseInt(age),

department:department,

email:email

})

})

.then(()=>loadStudents());

}