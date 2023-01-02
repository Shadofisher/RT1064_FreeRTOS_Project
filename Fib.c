int Fibonacci_GetElement(int num)
{
  int i; 
  int first=1;
  int second=1;
  int next = 1;
  if (num < 0)
    return 0;
  if ((num<=1) && (num >0))
  {
    return 1;
  }
  for (i = 2; i <= num; i++)
  {
    next = first +second;
    first = second;
    second  = next;
  }

return next;
}