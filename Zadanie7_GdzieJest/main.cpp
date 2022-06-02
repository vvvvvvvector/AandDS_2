#include <iostream>
#include <cstdio>
#include <ctime>

int room_number(int, int);

int main()
{
    int n_iter = 1000000;

    int start_HH, start_mm;
    scanf("%d:%d", &start_HH, &start_mm);

    int start_to_minutes = start_HH * 60 + start_mm;

    int end_HH, end_mm;
    scanf("%d:%d", &end_HH, &end_mm);

    int end_to_minute = end_HH * 60 + end_mm;

    int room;
    scanf("%d", &room);

    int rooms_count[6] = {0};

    for (int i = 0; i < n_iter; i++)
    {
        rooms_count[room_number(start_to_minutes, end_to_minute)]++;
    }

    printf("%.2lf", rooms_count[room] / (double)n_iter);

    return 0;
}

// int Grazyna(int HH, int mm)
// {
//     if (HH >= 8 && HH < 15)
//         return 0;
//     else if (HH >= 15 && HH < 22)
//         return 1;
//     return 2;
// }

int room_number(int start_minutes, int end_minutes)
{
    int range = end_minutes - start_minutes + 1;
    int time_from_range = rand() % range + start_minutes;

    return Grazyna(time_from_range / 60, time_from_range % 60);
}