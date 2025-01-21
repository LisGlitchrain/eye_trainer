#ifndef EYE_TRAINER_WRAPHELPER
#define EYE_TRAINER_WRAPHELPER 0

int wrapInt(int _Num,  int _Max)
{
    if(_Num < 0)
    {
        return (_Max + _Num % _Max);
    }
    if(_Num >= _Max)
    {
        return _Num % _Max;
    }

    return _Num;
}

int pingPong(int _Num,  int _MaxHalfIndex)
{
  const int maxHalfCount = _MaxHalfIndex + 1;
  const int maxFullIndex = _MaxHalfIndex * 2;
  const int maxFullCount = (_MaxHalfIndex + 1) * 2;
  int numInRange = _Num < 0 
  ? _Num % maxFullCount == 0 
    ? 0 
    : _Num % maxFullCount + maxFullCount 
  : _Num % maxFullCount;

  if(numInRange > _MaxHalfIndex)
  {
      return maxFullIndex - numInRange;
  }

  return numInRange;
}

int wrapInt(int _Num, int _Min, int _Max)
{
    int num = _Num - _Min;
    int max = _Max - _Min;
    return wrapInt(num, max) + _Min;
}

#endif