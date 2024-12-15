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

//Fix upper bounce (all LEDs are off)
int pingPong(int _Num,  int _Max)
{
    if(_Num < 0)
    {
        return (_Max + _Num % _Max);
    }
    if(_Num > _Max * 2)
    {
        return _Num % _Max;
    }
    if(_Num > _Max)
    {
        return _Max - _Num % _Max;
    }

    return _Num;
}

int wrapInt(int _Num, int _Min, int _Max)
{
    int num = _Num - _Min;
    int max = _Max - _Min;
    return wrapInt(num, max) + _Min;
}

#endif