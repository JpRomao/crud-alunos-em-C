#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define STUDENTS_QUANTITY 7
#define CLASSES_SPENT 50
#define MINIMUM_AVERAGE 6.0
#define MINIMUM_CLASSES_SPENT_PERCENT 75.0

typedef struct Student
{
  int number;
  char name[50];
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

void clearBuffer()
{
  while (getchar() != '\n' && getchar() != '\r')
  {
  }
}

void removeNewLineCharacter(char *string)
{
  string[strcspn(string, "\r\n")] = '\0';
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

  scanf("%i", &studentNumber);
  clearBuffer();

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

  scanf("%lf", &studentPoints);
  clearBuffer();

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

  scanf("%i", &watchedClasses);
  clearBuffer();

  if (watchedClasses < 0 || watchedClasses > CLASSES_SPENT)
  {
    printf("Houve um erro na quantidade de aulas assistidas. Digite novamente!\n");
    printf("Note que a quantidade de aulas nao pode ser menor que zero e nem maior que %d", CLASSES_SPENT);

    return inputStudentWatchedClasses();
  }

  return watchedClasses;
}

char *inputStudentName()
{
  char *studentName = malloc(50 * sizeof(char));

  printf("Digite o nome do aluno:");
  fgets(studentName, 50, stdin);
  removeNewLineCharacter(studentName);

  return studentName;
}

Student studentFactory()
{
  Student student;

  student.number = 0;
  strcpy(student.name, "\0");
  student.firstBimesterPoints = 0.0;
  student.secondBimesterPoints = 0.0;
  student.watchedClasses = 0;
  student.status = -1;

  return student;
}

void populateStudentArray(Student students[STUDENTS_QUANTITY])
{
  for (int i = 0; i < STUDENTS_QUANTITY; i++)
  {
    students[i] = studentFactory();
  }
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

void orderArrayByName(Student students[STUDENTS_QUANTITY])
{
  Student studentAux;

  for (int i = 0; i < STUDENTS_QUANTITY - 1; i++)
  {
    for (int j = i + 1; j < STUDENTS_QUANTITY; j++)
    {
      char *studentName = students[i].name;
      char *studentNameToCompare = students[j].name;

      int isNameBigger = strcmp(studentName, studentNameToCompare);

      if (isNameBigger > 0)
      {
        studentAux = students[i];
        students[i] = students[j];
        students[j] = studentAux;
      }
      else if (isNameBigger == 0)
      {
        if (students[i].number > students[j].number)
        {
          studentAux = students[i];
          students[i] = students[j];
          students[j] = studentAux;
        }
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

void printMenu()
{
  printf("\n\n");

  printf("Gerenciamento de dados\n");
  printf("======================================\n\n");

  printf("1. Listar todos os alunos\n");
  printf("2. Listar alunos aprovados\n");
  printf("3. Listar alunos em recuperacao\n");
  printf("4. Listar alunos reprovados\n");
  printf("5. Pesquisar alunos\n");
  printf("6. Incluir aluno\n");
  printf("7. Alterar aluno\n");
  printf("8. Eliminar aluno\n");
  printf("9. Sair do programa\n");
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

char *getStringfiedStudentStatus(int status)
{
  char *stringfiedStatus;

  switch (status)
  {
  case 0:
    stringfiedStatus = "Reprovado";
    break;
  case 1:
    stringfiedStatus = "Recuperacao";
    break;
  case 2:
    stringfiedStatus = "Aprovado";
    break;
  default:
    stringfiedStatus = "Status invalido";
    break;
  }

  return stringfiedStatus;
}

void listStudents(Student students[STUDENTS_QUANTITY])
{
  printf("Numero Aluno\tNome Aluno\tNota Bim. 1\tNota Bim. 2\tAulas Assistidas\tStatus\n");

  for (int i = 0; i < STUDENTS_QUANTITY; i++)
  {
    if (students[i].number <= 0 || students[i].status < 0 || students[i].status > 2)
    {
      continue;
    }

    char *stringfiedStatus = getStringfiedStudentStatus(students[i].status);

    printf(
        "%i\t\t%s\t\t%.2f\t\t%.2f\t\t%i\t\t\t%s\n",
        students[i].number,
        students[i].name,
        students[i].firstBimesterPoints,
        students[i].secondBimesterPoints,
        students[i].watchedClasses,
        stringfiedStatus);
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
  strcpy(newStudent.name, inputStudentName());
  newStudent.firstBimesterPoints = inputStudentPoints();
  newStudent.secondBimesterPoints = inputStudentPoints();
  newStudent.watchedClasses = inputStudentWatchedClasses();

  StudentStatusParameters parameters;
  parameters.firstNote = newStudent.firstBimesterPoints;
  parameters.secondNote = newStudent.secondBimesterPoints;
  parameters.watchedClasses = newStudent.watchedClasses;

  newStudent.status =
      calculateStudentStatus(parameters);

  int doesStudentInputed = 0;
  int i = 0;

  while (!doesStudentInputed)
  {
    if (students[i].number == 0)
    {
      students[i] = newStudent;

      doesStudentInputed = 1;
    }

    i++;
  }
}

void populateStudentsArrayForTest(Student students[STUDENTS_QUANTITY])
{
  students[0].number = 7;
  strcpy(students[0].name, "Joao");
  students[0].firstBimesterPoints = 10.0;
  students[0].secondBimesterPoints = 10.0;
  students[0].watchedClasses = 10;
  students[0].status = 1;

  students[1].number = 2;
  strcpy(students[1].name, "Maria");
  students[1].firstBimesterPoints = 10.0;
  students[1].secondBimesterPoints = 10.0;
  students[1].watchedClasses = 10;
  students[1].status = 0;

  students[2].number = 3;
  strcpy(students[2].name, "Jose");
  students[2].firstBimesterPoints = 10.0;
  students[2].secondBimesterPoints = 10.0;
  students[2].watchedClasses = 10;
  students[2].status = 0;

  students[3].number = 4;
  strcpy(students[3].name, "Pedro");
  students[3].firstBimesterPoints = 10.0;
  students[3].secondBimesterPoints = 10.0;
  students[3].watchedClasses = 10;
  students[3].status = 1;

  students[4].number = 5;
  strcpy(students[4].name, "Ana");
  students[4].firstBimesterPoints = 10.0;
  students[4].secondBimesterPoints = 10.0;
  students[4].watchedClasses = 10;
  students[4].status = 2;

  students[5].number = 6;
  strcpy(students[5].name, "Paulo");
  students[5].firstBimesterPoints = 10.0;
  students[5].secondBimesterPoints = 10.0;
  students[5].watchedClasses = 10;
  students[5].status = 2;

  students[6].number = 1;
  strcpy(students[6].name, "Joao");
  students[6].firstBimesterPoints = 10.0;
  students[6].secondBimesterPoints = 10.0;
  students[6].watchedClasses = 10;
  students[6].status = 2;
}

char *getStringInLowerCase(char *str)
{
  char *strLowerCase = (char *)malloc(strlen(str) + 1);
  strcpy(strLowerCase, str);

  for (int i = 0; str[i]; i++)
  {
    strLowerCase[i] = tolower(str[i]);
  }

  return strLowerCase;
}

void searchStudentLikeName(Student searchedStudents[STUDENTS_QUANTITY], Student students[STUDENTS_QUANTITY])
{
  populateStudentArray(searchedStudents);

  char name[50];

  printf("Digite o nome do aluno: ");
  fgets(name, 50, stdin);
  removeNewLineCharacter(name);

  printf("\n");

  printf("nome digitado: %s\n", name);

  printf("\n");

  char *nameLowerCase = getStringInLowerCase(name);

  for (int j = 0, i = 0; j < STUDENTS_QUANTITY; j++)
  {
    if (strstr(getStringInLowerCase(students[j].name), nameLowerCase) != NULL)
    {
      searchedStudents[i] = students[j];
      i++;
    }
    else
    {
      searchedStudents[j].number = 0;
    }
  }
}

void chooseMenuOption(Student students[STUDENTS_QUANTITY], int isAlreadySorted)
{
  printMenu();

  int option = 0;

  scanf("%i", &option);
  clearBuffer();

  printf("\n\n");

  Student reprovedStudents[STUDENTS_QUANTITY];
  Student recoveryStudents[STUDENTS_QUANTITY];
  Student approvedStudents[STUDENTS_QUANTITY];
  Student searchedStudents[STUDENTS_QUANTITY];

  if (!isAlreadySorted)
  {
    orderArrayByName(students);

    isAlreadySorted = 1;
  }

  switch (option)
  {
  case 1:
    listStudents(students);

    return chooseMenuOption(students, isAlreadySorted);
    break;
  case 2:
    cloneStudentsArray(students, approvedStudents);

    filterApprovedStudents(approvedStudents);

    listStudents(approvedStudents);

    return chooseMenuOption(students, isAlreadySorted);
    break;
  case 3:
    cloneStudentsArray(students, recoveryStudents);

    filterRecoveryStudents(recoveryStudents);

    listStudents(recoveryStudents);

    return chooseMenuOption(students, isAlreadySorted);
    break;
  case 4:
    cloneStudentsArray(students, reprovedStudents);

    filterReprovedStudents(reprovedStudents);

    listStudents(reprovedStudents);

    return chooseMenuOption(students, isAlreadySorted);
    break;
  case 5:
    searchStudentLikeName(searchedStudents, students);

    listStudents(searchedStudents);

    return chooseMenuOption(students, isAlreadySorted);
    break;
  case 6:
    createStudent(students);

    isAlreadySorted = 0;

    return chooseMenuOption(students, isAlreadySorted);
    break;
  case 7:
    updateStudent(students);

    isAlreadySorted = 0;

    return chooseMenuOption(students, isAlreadySorted);
    break;
  case 8:
    deleteStudent(students);

    isAlreadySorted = 1;

    return chooseMenuOption(students, isAlreadySorted);
    break;
  case 9:
    return;
    break;
  default:
    return chooseMenuOption(students, isAlreadySorted);
  }
}

int main()
{
  Student students[STUDENTS_QUANTITY];

  const char ENV[] = "development";
  int isAlreadySorted = 0;

  if (strcmp(ENV, "development") == 0)
  {
    populateStudentsArrayForTest(students);
  }
  else
  {
    populateStudentArray(students);
  }

  chooseMenuOption(students, isAlreadySorted);

  return 0;
}
