#include <stdio.h>
#include <string.h>

#define STUDENTS_QUANTITY 2
#define CLASSES_SPENT 50
#define MINIMUM_AVERAGE 6.0
#define MINIMUM_CLASSES_SPENT_PERCENT 75.0

typedef struct Student
{
  int number;
  double firstBimesterPoints;
  double secondBimesterPoints;
  int status;
  int watchedClasses;
} Student;

typedef struct StudentStatusParameters
{
  double firstNote;
  double secondNote;
  int watchedClasses;
} StudentStatusParameters;

int checkIfStudentNumberAlreadyInUse(Student students[STUDENTS_QUANTITY], int studentNumber)
{
  int exists = 0;

  for (int i = 0; i < STUDENTS_QUANTITY; i++)
  {
    if (students[i].number == studentNumber)
    {
      exists = 1;
    }
  }

  return exists;
}

int generateRandomStudentNumber(Student students[STUDENTS_QUANTITY])
{
  int studentNumber = 0;

  do
  {
    studentNumber = rand() % 10000;
  } while (checkIfStudentNumberAlreadyInUse(students, studentNumber));

  return studentNumber;
}

int inputStudentNumber()
{
  int studentNumber = 0;

  printf("Digite o numero do aluno:");
  fflush(stdin);
  scanf("%i", &studentNumber);

  if (studentNumber == 0)
  {
    printf("O numero do aluno nao pode ser 0. Digite novamente.\n");

    return inputStudentNumber();
  }

  return studentNumber;
}

double inputStudentPoints()
{
  double studentPoints = 0.0;

  printf("Digite a nota do aluno:");
  fflush(stdin);
  scanf("%lf", &studentPoints);

  if (studentPoints < 0.0 || studentPoints > 10.0)
  {
    printf("Houve um erro ao computar a nota do aluno. Digite novamente.\n");
    printf("Note que a nota do aluno deve ser no intervalo de 0 a 10.\n");

    return inputStudentPoints();
  }

  return studentPoints;
}

int inputStudentWatchedClasses()
{
  int watchedClasses = 0;

  printf("Digite a quantidade de aulas assistidas:");
  fflush(stdin);
  scanf("%i", &watchedClasses);

  if (watchedClasses < 0 || watchedClasses > CLASSES_SPENT)
  {
    printf("Houve um erro na quantidade de aulas assistidas. Digite novamente!\n");
    printf("Note que a quantidade de aulas nao pode ser menor que zero e nem maior que %d", CLASSES_SPENT);

    return inputStudentWatchedClasses();
  }

  return watchedClasses;
}

void cloneStudentsArray(Student students[STUDENTS_QUANTITY], Student clonedStudentsArray[STUDENTS_QUANTITY])
{
  for (int i = 0; i < STUDENTS_QUANTITY; i++)
  {
    clonedStudentsArray[i].number = students[i].number;
    clonedStudentsArray[i].firstBimesterPoints = students[i].firstBimesterPoints;
    clonedStudentsArray[i].secondBimesterPoints = students[i].secondBimesterPoints;
    clonedStudentsArray[i].watchedClasses = students[i].watchedClasses;
    clonedStudentsArray[i].status = students[i].status;
  }
}

void orderArrayByNumberAscending(Student students[STUDENTS_QUANTITY])
{
  Student studentAux;

  for (int i = 0; i < STUDENTS_QUANTITY; i++)
  {
    for (int j = 0; j < STUDENTS_QUANTITY; j++)
    {
      if (students[i].number < students[j].number)
      {
        studentAux = students[i];
        students[i] = students[j];
        students[j] = studentAux;
      }
    }
  }
}

void updateStudent(Student students[STUDENTS_QUANTITY])
{
  int studentNumber = inputStudentNumber();

  int studentExists = checkIfStudentNumberAlreadyInUse(students, studentNumber);

  if (!studentExists)
  {
    printf("O numero do aluno nao existe, digite novamente!\n");

    return updateStudent(students);
  }

  int stop = 0;

  int i = 0;

  while (!stop)
  {
    if (students[i].number == studentNumber)
    {
      students[i].firstBimesterPoints = inputStudentPoints();
      students[i].secondBimesterPoints = inputStudentPoints();
      students[i].watchedClasses = inputStudentWatchedClasses();

      StudentStatusParameters parameters;
      parameters.firstNote = students[i].firstBimesterPoints;
      parameters.secondNote = students[i].secondBimesterPoints;
      parameters.watchedClasses = students[i].watchedClasses;

      students[i].status =
          calculateStudentStatus(parameters);

      stop = 1;
    }

    if (i == STUDENTS_QUANTITY)
    {
      printf("O numero do aluno nao existe, digite novamente!\n");

      studentNumber = inputStudentNumber();

      i = 0;

      continue;
    }

    i++;
  }
}

void deleteStudent(Student students[STUDENTS_QUANTITY])
{
  int studentToDeleteNumber = inputStudentNumber();

  for (int i = 0; i < STUDENTS_QUANTITY; i++)
  {
    if (students[i].number == studentToDeleteNumber)
    {
      students[i].number = 0;
    }
  }
}

double calculateStudentFrequencyPercent(int watchedClasses)
{
  return (watchedClasses * 100) / CLASSES_SPENT;
}

int calculateStudentStatus(StudentStatusParameters parameters)
{
  double averageNote = (parameters.firstNote + parameters.secondNote) / 2;
  int status = 0;
  double studentFrequency = calculateStudentFrequencyPercent(parameters.watchedClasses);

  if (averageNote >= 6 && studentFrequency >= 75)
  {
    status = 2;
  }
  else if (averageNote < 6 && averageNote >= 3 && studentFrequency >= 75)
  {
    status = 1;
  }

  return status;
}

void printMenu()
{
  printf("\n\n");

  printf("Gerenciamento de dados\n");
  printf("======================================\n\n");

  printf("1. Listar todos os alunos\n");
  printf("2. Listar alunos aprovados\n");
  printf("3. Listar alunos em recuperacao\n");
  printf("4. Listar alunos reprovados\n");
  printf("5. Incluir aluno\n");
  printf("6. Alterar aluno\n");
  printf("7. Eliminar aluno\n");
  printf("8. Sair do programa\n");
}

void filterApprovedStudents(Student students[STUDENTS_QUANTITY])
{
  Student approvedStudents[STUDENTS_QUANTITY];

  for (int i = 0; i < STUDENTS_QUANTITY; i++)
  {
    if (students[i].status == 2)
    {
      approvedStudents[i] = students[i];
    }
    else
    {
      approvedStudents[i].number = 0;
      approvedStudents[i].firstBimesterPoints = 0.0;
      approvedStudents[i].secondBimesterPoints = 0.0;
      approvedStudents[i].watchedClasses = 0;
      approvedStudents[i].status = 0;
    }
  }

  for (int i = 0; i < STUDENTS_QUANTITY; i++)
  {
    students[i] = approvedStudents[i];
  }
}

void filterReprovedStudents(Student students[STUDENTS_QUANTITY])
{
  Student reprovedStudents[STUDENTS_QUANTITY];

  for (int i = 0; i < STUDENTS_QUANTITY; i++)
  {
    if (students[i].status == 0)
    {
      reprovedStudents[i] = students[i];
    }
    else
    {
      reprovedStudents[i].number = 0;
      reprovedStudents[i].firstBimesterPoints = 0.0;
      reprovedStudents[i].secondBimesterPoints = 0.0;
      reprovedStudents[i].watchedClasses = 0;
      reprovedStudents[i].status = 0;
    }

    for (int i = 0; i < STUDENTS_QUANTITY; i++)
    {
      students[i] = reprovedStudents[i];
    }
  }
}

void filterRecoveryStudents(Student students[STUDENTS_QUANTITY])
{
  Student recoveryStudents[STUDENTS_QUANTITY];

  for (int i = 0; i < STUDENTS_QUANTITY; i++)
  {
    if (students[i].status == 1)
    {
      recoveryStudents[i] = students[i];
    }
    else
    {
      recoveryStudents[i].number = 0;
      recoveryStudents[i].firstBimesterPoints = 0.0;
      recoveryStudents[i].secondBimesterPoints = 0.0;
      recoveryStudents[i].watchedClasses = 0;
      recoveryStudents[i].status = 0;
    }
  }

  for (int i = 0; i < STUDENTS_QUANTITY; i++)
  {
    students[i] = recoveryStudents[i];
  }
}

void listStudents(Student students[STUDENTS_QUANTITY])
{
  printf("Numero Aluno\tNota Bim. 1\tNota Bim. 2\tAulas Assistidas\tStatus\n");

  for (int i = 0; i < STUDENTS_QUANTITY; i++)
  {
    if (students[i].number <= 0 || students[i].status < 0 || students[i].status > 2)
    {
      continue;
    }

    printf(
        "%i\t\t%.2f\t\t%.2f\t\t%i\t\t\t%i\n",
        students[i].number,
        students[i].firstBimesterPoints,
        students[i].secondBimesterPoints,
        students[i].watchedClasses,
        students[i].status);
  }
}

int arrayLength(Student students[STUDENTS_QUANTITY])
{
  int length = 0;

  for (int i = 0; i < STUDENTS_QUANTITY; i++)
  {
    if (students[i].number != 0)
    {
      length++;
    }
  }

  return length;
}

void createStudent(Student students[STUDENTS_QUANTITY])
{
  if (arrayLength(students) == STUDENTS_QUANTITY)
  {
    printf("Nao ha mais espaco para novos alunos");
    return;
  }

  Student newStudent;
  newStudent.number = generateRandomStudentNumber(students);
  newStudent.firstBimesterPoints = inputStudentPoints();
  newStudent.secondBimesterPoints = inputStudentPoints();
  newStudent.watchedClasses = inputStudentWatchedClasses();

  StudentStatusParameters parameters;
  parameters.firstNote = newStudent.firstBimesterPoints;
  parameters.secondNote = newStudent.secondBimesterPoints;
  parameters.watchedClasses = newStudent.watchedClasses;

  newStudent.status =
      calculateStudentStatus(parameters);

  int stop = 1;
  int i = 0;

  while (stop)
  {
    if (students[i].number == 0)
    {
      students[i] = newStudent;

      stop = 0;
    }

    i++;
  }
}

Student studentFactory()
{
  Student student;

  student.number = 0;
  student.firstBimesterPoints = 0.0;
  student.secondBimesterPoints = 0.0;
  student.watchedClasses = 0;
  student.status = -1;

  return student;
}

void chooseMenuOption(Student students[STUDENTS_QUANTITY])
{
  printMenu();

  int option = 0;

  scanf("%i", &option);
  printf("\n\n");

  Student reprovedStudents[STUDENTS_QUANTITY];
  Student recoveryStudents[STUDENTS_QUANTITY];
  Student approvedStudents[STUDENTS_QUANTITY];

  switch (option)
  {
  case 1:
    listStudents(students);

    return chooseMenuOption(students);
    break;
  case 2:
    cloneStudentsArray(students, approvedStudents);

    filterApprovedStudents(approvedStudents);

    listStudents(approvedStudents);

    return chooseMenuOption(students);
    break;
  case 3:
    cloneStudentsArray(students, recoveryStudents);

    filterRecoveryStudents(recoveryStudents);

    listStudents(recoveryStudents);

    return chooseMenuOption(students);
    break;
  case 4:
    cloneStudentsArray(students, reprovedStudents);

    filterReprovedStudents(reprovedStudents);

    listStudents(reprovedStudents);

    return chooseMenuOption(students);
    break;
  case 5:
    createStudent(students);

    return chooseMenuOption(students);
    break;
  case 6:
    updateStudent(students);

    return chooseMenuOption(students);
    break;
  case 7:
    deleteStudent(students);

    return chooseMenuOption(students);
    break;
  case 8:
    return;
    break;
  default:
    return chooseMenuOption(students);
  }
}

void populateStudentArray(Student students[STUDENTS_QUANTITY])
{
  for (int i = 0; i < STUDENTS_QUANTITY; i++)
  {
    students[i] = studentFactory();
  }
}

int main()
{
  Student students[STUDENTS_QUANTITY];

  populateStudentArray(students);

  chooseMenuOption(students);

  return 0;
}