float pi=3.1416;

float c(){
    int d = 0;
    return d;
}

float sqr(float num)
{
  return (num*num);
}

float calarea(int r)
{
  float area, tmp;
  tmp = sqr(r);
  area = pi * sqr(r);
  return area;
}

int floor(float num)
{
  int temp;
  temp = num;
  return temp;
}

int MAIN(){
  
  int r;
  float area;
  float rem;
  write("Enter an Integer :"); 
  r=read();

  area=calarea(r);
  rem=area-floor(area);

  write(area);
  write(" ");
  write(rem);
  write("\n");

  return 0;
}
