// js/app.js
function addTask() {
  const taskInput = document.getElementById("taskInput");
  const taskList = document.getElementById("taskList");
  const taskText = taskInput.value.trim();

  if (taskText !== "") {
    const li = document.createElement("li");
    li.textContent = taskText;
    li.onclick = () => li.remove(); // click to remove task
    taskList.appendChild(li);
    taskInput.value = "";
  }
}