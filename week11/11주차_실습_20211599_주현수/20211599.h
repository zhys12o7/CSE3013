#pragma once
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

char** mapp;
int** c;
int cnt;
int n, m;

void init(void);
void maze(void);
void equalize(int a, int b);
void print(void);
int mn(int a, int b);
