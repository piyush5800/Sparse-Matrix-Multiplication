#include<iostream>
using namespace std;

class node                                      //node for each element of matrix
{
public:
  int row;
  int column;
  int data;
  node*next;
};

//This is a class that represents a matrix and has the member functions for
//making an new node, getting a new matric from user, printing a matrix and
//transposing a matrix
class matrix
{
public:
  node*head;                                     //pointer to first element
  int m;                                         //Number of rows [0...m-1]
  int n;                                         //Number of columns [0...n-1]

  matrix()                                       //Constructor Function
  {
    head = NULL;
    m=0;
    n=0;
  }

  void newNode(int data, int m, int n)           //Function to add new element to matrix
  {

    node*newn = new node;
    newn->row = m;
    newn->column = n;
    newn->data = data;
    newn->next = NULL;
    if(head == NULL)
      head = newn;
    else
    {
      node*temp = head;
      while(temp->next!=NULL)
      {
        temp = temp->next;
      }
      temp->next = newn;
    }
  }

  void getMatrix()                               //Function to get the matrix as input from user
  {
    cout<<"Enter the no. of rows of the matrix: ";
    int temp;
    cin>>m;
    cout<<"Enter the no. of columns of the matrix: ";
    cin>>n;
    cout<<"Please enter the matrix in row wise order: "<<endl;
    for(int i=0 ;i<m; i++)
    {
      for(int j=0; j<n; j++)
      {
        cin>>temp;
        if(temp!=0)
          newNode(temp, i, j);
      }
    }
  }

  void printMatrix()                             //Function to print the matrix
  {
    node*temp = head;
    for(int i=0 ;i<m; i++)
    {
      for(int j=0; j<n ; j++)
      {
        if(temp == NULL)
          cout<<'0'<<"  ";
        else if(temp->row == i && temp->column == j)
        {
          cout<<temp->data<<"  ";
          temp = temp->next;
        }
        else
          cout<<'0'<<"  ";
      }
      cout<<endl;
    }
  }

  void transpose()                               //Function to transpose a matrix
  {
    //Initialize an empty new matrix result
    matrix result;
    result.head=NULL;
    result.m = n;
    result.n = m;

    //Traverse the matrix for each and every column
    //Put nodes into result matrix as you find them
    int counter = 0;
    node*temp = head;
    while(counter < n)
    {
      while(temp != NULL)
      {
        if(temp->column == counter)
          result.newNode(temp->data, temp->column, temp->row);
        temp = temp->next;
      }
      counter++;
      temp = head;
    }
    head = result.head;
    m = result.m;
    n = result.n;
    return;
  }
};

matrix multiplyMatrix(matrix m1, matrix m2)      //Function to multiply the matrices m1 and m2
{
  matrix res;
  if(m1.n != m2.m)
  {
    cout<<"The matrices cannot be multiplied. They have the wrong dimensions.";
    cout<<endl<<"An empty matrix has been returned.";
    return res;
  }
  m2.transpose();

  res.m = m1.m;
  res.n = m2.m;

  node* temp1 = m1.head;
  node* temp2 = m2.head;

  while(temp1 !=NULL)
  {
    int row = temp1->row;
    temp2 = m2.head;
    while(temp2!=NULL)
    {
      int col = temp2->row;

      node* tempa = temp1;
      node* tempb = temp2;
      int sum = 0;

      while(tempa!=NULL && tempa->row == row && tempb!=NULL && tempb->row == col)
      {
        if(tempa->column < tempb->column)
          tempa = tempa->next;
        else if (tempa->column > tempb->column)
          tempb = tempb->next;
        else
        {
          sum += tempa->data * tempb->data;
          tempa = tempa->next;
          tempb = tempb->next;
        }
      }
      if(sum!=0)
        res.newNode(sum, row, col);

      while(temp2!=NULL && temp2->row == col)
        temp2 = temp2->next;
    }
    while(temp1!=NULL && temp1->row == row)
      temp1 = temp1->next;
  }
  return res;
}

int main()                                       //MAIN PROGRAM
{
  matrix m1, m2;
  m1.getMatrix();
  cout<<endl;
  m2.getMatrix();
  cout<<endl;
  matrix r = multiplyMatrix(m1, m2);
  cout<<"The multiplied matrix is:"<<endl;
  cout<<"Dimensions: "<<r.m<<"x"<<r.n<<endl;
  r.printMatrix();
  return 0;
}
