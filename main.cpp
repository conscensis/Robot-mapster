#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cmath>

using namespace std;

const float PI = 3.1415;    // pi
const float Radius = 3;     // радиус колеса
const float Distwheel= 14;  // расстояние между колсами
const float TimewheelR = 1;  // об/сек
const float TimewheelL = 1;  // об/сек
const float Radian = 57.2957795; //1 рад = 57.2957795 градусов
float points[10][361];




class mapster
{
public:
    float distance;
    float engineTimeR;
    float engineTimeL;
    float length;
    float degree;

float getDistance()
{
    //distance = pin11;  //снимаем показания с датчика
    return distance;
}
float getDegree()
{
    return degree;
}
float getLength()
{
    return length;
}
float getDistancePoints(int z)
{
    for(int i=0;i<=361;i++)            //крутим робота по 1 градусу 360 градусов
    {                                  //и пишем в массив расстояние
        setDegree(i);
        points[z][i]=getDistance();
    }
}



void setEngneTimeR(float R)
{
   engineTimeR = R;                          //время которое должно крутиться колесо R
}
void setEngineTimeL(float L)
{
    engineTimeL = L;                           //время которое должно крутиться колесо L
}
void setLength(float newLength)
{
 float alpha,timeR,timeL,oborot;       //alpha - нужно повернуть колеса в градусах что бы пройти расстояние mewLength c радиусом колес Radius
                                //timeR и timeL время рассчитаное для колес с разными скоростями вращения об/с
                                //что бы пройти расстояние newLength не поворачивая эдакий Пи регулятор

 alpha=(newLength*180)/(PI*Radius);   //кол градусов для преодоления расстояния newLength
 oborot=alpha/Radian;                 //кол оборотов для колес при 1 рад = 57.2957795 градусов
 timeR=oborot/TimewheelR;             //время для нужного количество оборотов для колеса R
 timeL=oborot/TimewheelL;             //время для нужного количество оборотов для колеса L
 setEngneTimeR(timeR);                //присвоить время для вращения колеса R
 setEngineTimeL(timeL);                //присвоить время для вращения колеса L
 length+=newLength;                    //присвоить пройденое расстояние
                                      //НЕ УЧИТЫВАЕТСЯ ПРОКРУЧИВАНИЕ КОЛЕС, И ПОВЕРХНОСТЬ СЧИТАЕТСЯ АБСОЛЮТНО ГЛАДКОЙ

}
void setDegree(float deg)
{
    float grad,a,alpha,oborot,time;
    grad = degree-deg;

    if (grad<0)
    {
     a=Distwheel*tan(deg);             //катет треугольника равный длине которое нужно пройти колесу что бы повернуть на угол deg
     alpha=(a*180)/(PI*Radius);        //кол градусов требуемое для прохождения расстояния a одним колесом
     oborot=alpha/Radian;              //кол оборотов для колеса для прохождения расстояния a
     time=oborot/TimewheelR;           //время для совершения oborot колесом R
     setEngneTimeR(time);              //присвоить колесу R время вращения для достижения угла deg
     degree+=deg;                       //присвоить успешное поворачивание робота
                                       //НЕ УЧИТЫВАЕТСЯ ПРОКРУЧИВАНИЕ КОЛЕС И ПОГРЕШНОСТЬ РАДИУСВЕКТОРА ПРИ ПОВОРОТЕ ТОЛЬКО ОДНИМ КОЛЕСОМ
    }
    else
    {
        a=Distwheel*tan(deg);
        alpha=(a*180)/(PI*Radius);
        oborot=alpha/Radian;             //время для совершения oborot колесом L
        time=oborot/TimewheelL;          //присвоить колесу L время вращения для достижения угла deg
        setEngineTimeL(time);
        degree+=deg;
    }
}


void setCoordinate(float length,float degree)     //переместиться в пространстве с помощью радиус вектора (задается длина и угол)
{

   setDegree(degree);   //передать угол на который нужно повернуться
   setLength(length);   //передать расстояние которое нужно пройти

}


};


int main()
{
mapster r;
r.length=0;  //начальная установка робота нулевое расстояния от начала координат
r.degree=0;  //начальная установка робота нулевой градус от начала отсчета градусов

for(int i=0;i<10;i++)
{
r.getDistancePoints(i);
r.setCoordinate(30,36); // пройдет расстояние 30 см под углом 45 градусов и снимет 360 координат точек которые его окружают
                        //в данном случае получится шестиугольник со сторонами 30 см, т.к угол 36 градусов с 10 итерациями получится многоугольник
                        //в результате получим 10 массивов с координатами точек получеными с дальномера по 360 точек в массиве
}




}


