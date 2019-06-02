#pragma once
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <Windows.h>
#include "sqlite3.h"
#include <vector>
using namespace std;

extern vector<string> wordlist;

static int callback(void *data, int argc, char **argv, char **azColName);

BOOL GetWordsFromDatabase(const char *db_name);

