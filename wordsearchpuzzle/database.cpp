#include "database.h"

static int callback(void *data, int argc, char **argv, char **azColName) {
	int i;
	//fprintf(stderr, "%s: ", (const char*)data);
	for (i = 0; i < argc; i++) {
		//printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		string temp(argv[i]);
		wordlist.push_back(temp);
	}
	printf("\n");
	return 0;
}

BOOL GetWordsFromDatabase(const char *db_name)
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	const char* data = "Callback function called";

	/* Open database */
	rc = sqlite3_open(db_name, &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}

	/* Create SQL statement */
	char sql[] = "SELECT * from list";//"select name from sqlite_master where type='table' order by name";//

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	/*
	vector<string> ::iterator it1;
	for (it1 = wordlist.begin(); it1 != wordlist.end(); it1++)
		cout << *it1 << endl;*/
	sqlite3_close(db);
	return 0;
}