hljs.highlightAll();


function sendMail() {
    const templateParams = {
        name: document.getElementById("name").value,
        email: document.getElementById("email").value,
        message: document.getElementById("message").value
    };

    if (!nameField.value || !emailField.value || !messageField.value) {
        feedback.innerHTML =
            "<span class='text-danger'>❌ Please fill all required fields.</span>";
        return;
    }

    const params = {
        name: nameField.value,
        email: emailField.value,
        message: messageField.value,
    };

    emailjs
        .send("service_bb7ho0a", "template_uuij7uq", params)
        .then(() => {
            feedback.innerHTML =
                "<span class='text-success'>✔ Message sent successfully!</span>";
            nameField.value = "";
            emailField.value = "";
            messageField.value = "";
        })
        .catch(() => {
            feedback.innerHTML =
                "<span class='text-danger'>❌ Failed to send message. Please try again.</span>";
        });
}


const employees = [
    {
        id: 101,
        name: "Alice Johnson",
        position: "HR Manager",
        salary: 75000,
    },
    {
        id: 102,
        name: "Bob Smith",
        position: "Developer",
        salary: 68000,
    },
    {
        id: 103,
        name: "Charlie Davis",
        position: "Designer",
        salary: 62000,
    },
    {
        id: 104,
        name: "Diana Evans",
        position: "QA Engineer",
        salary: 60000,
    },
    {
        id: 105,
        name: "Ethan Wilson",
        position: "Payroll Specialist",
        salary: 58000,
    },
    {
        id: 106,
        name: "Fiona Clark",
        position: "Recruiter",
        salary: 55000,
    },
    {
        id: 107,
        name: "George Lee",
        position: "Developer",
        salary: 70000,
    },
    {
        id: 108,
        name: "Hannah Kim",
        position: "HR Assistant",
        salary: 48000,
    },
    {
        id: 109,
        name: "Ian Martinez",
        position: "System Analyst",
        salary: 72000,
    },
    {
        id: 110,
        name: "Julia Roberts",
        position: "Team Lead",
        salary: 82000,
    },
    { id: 111, name: "Kevin Brown", position: "Intern", salary: 32000 },
    {
        id: 112,
        name: "Laura Wilson",
        position: "Developer",
        salary: 67000,
    },
    {
        id: 113,
        name: "Michael Scott",
        position: "Regional Manager",
        salary: 95000,
    },
    {
        id: 114,
        name: "Nina Patel",
        position: "Data Scientist",
        salary: 88000,
    },
    { id: 115, name: "Oscar Tran", position: "QA Lead", salary: 75000 },
    {
        id: 116,
        name: "Pam Beesly",
        position: "Receptionist",
        salary: 42000,
    },
    {
        id: 117,
        name: "Quincy Adams",
        position: "Developer",
        salary: 69000,
    },
    {
        id: 118,
        name: "Rachel Green",
        position: "HR Specialist",
        salary: 61000,
    },
    {
        id: 119,
        name: "Steve Rogers",
        position: "Security Officer",
        salary: 55000,
    },
    {
        id: 120,
        name: "Tina Turner",
        position: "Payroll Manager",
        salary: 78000,
    },
];

const rowsPerPage = 5;
let currentPage = 1;
let currentSortColumn = null;
let currentSortAsc = true;
let currentSearchTerm = "";

const employeeTableBody = document.querySelector(
    "#employeeTable tbody"
);
const paginationContainer = document.getElementById("pagination");
const searchInput = document.getElementById("searchInput");
const resultCountSpan = document.getElementById("resultCount");

function sortEmployees(data, key, asc = true) {
    return data.slice().sort((a, b) => {
        if (typeof a[key] === "string") {
            return asc
                ? a[key].localeCompare(b[key])
                : b[key].localeCompare(a[key]);
        }
        if (typeof a[key] === "number") {
            return asc ? a[key] - b[key] : b[key] - a[key];
        }
        return 0;
    });
}

function renderTable() {
    let filteredEmployees = employees.filter(
        (emp) =>
            emp.name.toLowerCase().includes(currentSearchTerm) ||
            emp.id.toString().includes(currentSearchTerm)
    );

    resultCountSpan.textContent = filteredEmployees.length;

    if (currentSortColumn) {
        filteredEmployees = sortEmployees(
            filteredEmployees,
            currentSortColumn,
            currentSortAsc
        );
    }

    const totalPages = Math.ceil(
        filteredEmployees.length / rowsPerPage
    );
    if (currentPage > totalPages) currentPage = 1;

    const startIndex = (currentPage - 1) * rowsPerPage;
    const paginatedEmployees = filteredEmployees.slice(
        startIndex,
        startIndex + rowsPerPage
    );

    employeeTableBody.innerHTML = "";
    paginatedEmployees.forEach((emp) => {
        const tr = document.createElement("tr");
        tr.setAttribute("tabindex", "0");
        tr.setAttribute("role", "button");
        tr.setAttribute("aria-label", `View details for ${emp.name}`);
        tr.innerHTML = `
          <td>${emp.id}</td>
          <td>${emp.name}</td>
          <td>${emp.position}</td>
          <td>${emp.salary.toLocaleString(undefined, {
            minimumFractionDigits: 2,
            maximumFractionDigits: 2,
        })}</td>
        `;
        tr.addEventListener("click", () => showEmployeeDetails(emp));
        tr.addEventListener("keypress", (e) => {
            if (e.key === "Enter" || e.key === " ") {
                e.preventDefault();
                showEmployeeDetails(emp);
            }
        });
        employeeTableBody.appendChild(tr);
    });

    renderPagination(totalPages);
}

function renderPagination(totalPages) {
    paginationContainer.innerHTML = "";

    function createPageItem(page) {
        const li = document.createElement("li");
        li.classList.add("page-item");
        if (page === currentPage) {
            li.classList.add("active");
        }
        const a = document.createElement("a");
        a.classList.add("page-link");
        a.href = "#employeeDirectory";
        a.textContent = page;
        a.addEventListener("click", (e) => {
            e.preventDefault();
            if (page !== currentPage) {
                currentPage = page;
                renderTable();
            }
        });
        li.appendChild(a);
        return li;
    }

    const prevLi = document.createElement("li");
    prevLi.classList.add("page-item");
    if (currentPage === 1) prevLi.classList.add("disabled");
    const prevA = document.createElement("a");
    prevA.classList.add("page-link");
    prevA.href = "#employeeDirectory";
    prevA.setAttribute("aria-label", "Previous page");
    prevA.innerHTML = "&laquo;";
    prevA.addEventListener("click", (e) => {
        e.preventDefault();
        if (currentPage > 1) {
            currentPage--;
            renderTable();
        }
    });
    prevLi.appendChild(prevA);
    paginationContainer.appendChild(prevLi);

    if (totalPages <= 7) {
        for (let i = 1; i <= totalPages; i++) {
            paginationContainer.appendChild(createPageItem(i));
        }
    } else {

        if (currentPage > 4) {
            paginationContainer.appendChild(createPageItem(1));
            const ellipsis1 = document.createElement("li");
            ellipsis1.classList.add("page-item", "disabled");
            ellipsis1.innerHTML = '<span class="page-link">...</span>';
            paginationContainer.appendChild(ellipsis1);
        }
        const startPage = Math.max(1, currentPage - 2);
        const endPage = Math.min(totalPages, currentPage + 2);
        for (let i = startPage; i <= endPage; i++) {
            paginationContainer.appendChild(createPageItem(i));
        }
        if (currentPage < totalPages - 3) {
            const ellipsis2 = document.createElement("li");
            ellipsis2.classList.add("page-item", "disabled");
            ellipsis2.innerHTML = '<span class="page-link">...</span>';
            paginationContainer.appendChild(ellipsis2);
            paginationContainer.appendChild(createPageItem(totalPages));
        }
    }

    const nextLi = document.createElement("li");
    nextLi.classList.add("page-item");
    if (currentPage === totalPages) nextLi.classList.add("disabled");
    const nextA = document.createElement("a");
    nextA.classList.add("page-link");
    nextA.href = "#employeeDirectory";
    nextA.setAttribute("aria-label", "Next page");
    nextA.innerHTML = "&raquo;";
    nextA.addEventListener("click", (e) => {
        e.preventDefault();
        if (currentPage < totalPages) {
            currentPage++;
            renderTable();
        }
    });
    nextLi.appendChild(nextA);
    paginationContainer.appendChild(nextLi);
}


document
    .querySelectorAll("#employeeTable thead th[data-sort]")
    .forEach((th) => {
        th.style.userSelect = "none";
        th.addEventListener("click", () => {
            const col = th.getAttribute("data-sort");
            if (currentSortColumn === col) {
                currentSortAsc = !currentSortAsc;
            } else {
                currentSortColumn = col;
                currentSortAsc = true;
            }
            renderTable();
            updateSortIndicators();
        });
    });

function updateSortIndicators() {
    document
        .querySelectorAll("#employeeTable thead th[data-sort]")
        .forEach((th) => {
            th.classList.remove("sorting-asc", "sorting-desc");
            if (th.getAttribute("data-sort") === currentSortColumn) {
                th.classList.add(
                    currentSortAsc ? "sorting-asc" : "sorting-desc"
                );
            }
        });
}


function showEmployeeDetails(emp) {
    const modalBody = document.getElementById("employeeDetailBody");
    modalBody.innerHTML = `
        <ul class="list-group">
          <li class="list-group-item"><strong>ID:</strong> ${emp.id}</li>
          <li class="list-group-item"><strong>Name:</strong> ${emp.name}</li>
          <li class="list-group-item"><strong>Position:</strong> ${emp.position
        }</li>
          <li class="list-group-item"><strong>Salary:</strong> $${emp.salary.toLocaleString(
            undefined,
            { minimumFractionDigits: 2, maximumFractionDigits: 2 }
        )}</li>
        </ul>
      `;
    const employeeModal = new bootstrap.Modal(
        document.getElementById("employeeDetailModal")
    );
    employeeModal.show();
}


searchInput.addEventListener("input", (e) => {
    currentSearchTerm = e.target.value.trim().toLowerCase();
    currentPage = 1;
    renderTable();
});


renderTable();


const contactForm = document.getElementById("contactForm");
const formFeedback = document.getElementById("formFeedback");
contactForm.addEventListener("submit", (e) => {
    e.preventDefault();
    formFeedback.textContent = "";
    formFeedback.className = "";

    if (!contactForm.checkValidity()) {
        contactForm.classList.add("was-validated");
        formFeedback.textContent =
            "Please fill out all required fields correctly.";
        formFeedback.classList.add("text-danger");
        return;
    }


    formFeedback.textContent = "Sending message...";
    formFeedback.classList.add("text-info");

    setTimeout(() => {
        contactForm.reset();
        contactForm.classList.remove("was-validated");
        formFeedback.textContent =
            "Thank you for your message! I will get back to you soon.";
        formFeedback.classList.remove("text-info");
        formFeedback.classList.add("text-success");
    }, 1500);
});


const tooltipTriggerList = [].slice.call(
    document.querySelectorAll('[data-bs-toggle="tooltip"]')
);
tooltipTriggerList.map(
    (tooltipTriggerEl) => new bootstrap.Tooltip(tooltipTriggerEl)
);

document.addEventListener("click", function (event) {
    const navbar = document.querySelector(".navbar-collapse");
    if (navbar.classList.contains("show")) {
        const isLink = event.target.closest(".nav-link");
        if (isLink) {
            const bsCollapse = new bootstrap.Collapse(navbar, {
                toggle: true
            });
        }
    }
});