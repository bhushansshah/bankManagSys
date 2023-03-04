#include "mysqlFunc.h"
#include "supportFunc.h"
void insertUser(MYSQL **con, int userid, char *password, char *firstName, char *middleName, char *lastName, long long int phoneNo, char *email, char *address, char *city, char *state, char *country, char *branch){
	char query[500];
	static int count = 0;
	count++;
	sprintf(query, "insert into customers_info(userid, password, first_name, middle_name, last_name, branch, email, address, city, state, country, balance) values(%d, '%s', '%s', '%s', '%s', '%s','%s', '%s', '%s', '%s', '%s', '0');", userid, password, firstName, middleName, lastName, branch, email, address, city, state, country);
	mysql_query(*con, query);
	printf("%d", count);
}

int isValidUserid(MYSQL **con, int userid){
	MYSQL_RES *res;
	MYSQL_ROW row;
	int iter = 0;
	mysql_query(*con, "select userid from customers_info;");
	res = mysql_store_result(*con);
	while(row = mysql_fetch_row(res)){
		iter++;
		if(userid == toInt(row[0])){
			mysql_free_result(res);
			return 1;
		}
	}
//	printf("Hi i am here\n");
	mysql_free_result(res);
	return 0;
}

int isValidPassword(MYSQL **con, int userid, char *password){
	MYSQL_RES *res; 
	MYSQL_ROW row;
	char query[100];
	int result = 0;
	sprintf(query, "select password from customers_info where userid = %d;", userid);
	mysql_query(*con, query);
	res = mysql_store_result(*con);
	if(row = mysql_fetch_row(res)){
		result = isStringEqual(password, row[0]);
	}
	mysql_free_result(res);
	return result;

}

int getBalance(MYSQL **con, int userid){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[100];
	sprintf(query, "select balance from customers_info where userid = %d;", userid);
	mysql_query(*con, query);
	res = mysql_store_result(*con);
	row = mysql_fetch_row(res);
	int balance = toInt(row[0]);
	mysql_free_result(res);
	return balance;
}

int isWithdrawalPossible(MYSQL **con, int userid, int withdrawAmount){
	return getBalance(con, userid) >= withdrawAmount;
}

void withdraw(MYSQL **con, int userid, int withdrawAmount){
	int balance = getBalance(con, userid);
	int newBal = balance - withdrawAmount;
	char query[100];
	sprintf(query, "update customers_info set balance = '%d' where userid = %d;",newBal, userid);
	mysql_query(*con, query);
}
void deposit(MYSQL **con, int userid, int depositAmount){
	int balance = getBalance(con, userid);
	int newBal = balance + depositAmount;
	char query[100];
	sprintf(query, "update customers_info set balance = '%d' where userid = %d;", newBal, userid);
	mysql_query(*con, query);
}
void printProfile(MYSQL **con, int userid){
	char query[100];
	MYSQL_RES *res;
	MYSQL_ROW row;
	sprintf(query, "select * from customers_info where userid = %d;", userid);
	mysql_query(*con, query);
	res = mysql_store_result(*con);
	row = mysql_fetch_row(res);
	printf("----Profile Details----\n");
	printf("First Name : %s\n", row[2]);
	printf("Middle Name : %s\n", row[3]);
	printf("Last Name : %s\n", row[4]);
	printf("Userid : %s\n", row[0]);
	printf("Account No. : %s\n", row[6]);
	printf("Branch: %s\n", row[7]);
	printf("Email id : %s\n", row[9]);
	printf("Address : %s\n", row[10]);
	printf("City: %s\n", row[11]);
	printf("State: %s\n", row[12]);
	printf("Country: %s\n", row[13]);
	mysql_free_result(res);
}
void updateProfile(MYSQL **con, int userid){
	int option;
	char input[100];
	char ch;
	int i = 0;
	printf("----Profile update----\n");
	printf("1) First Name\n");
	printf("2) Middle Name\n");
	printf("3) Last Name\n");
	printf("4) Branch\n");
	printf("5) Email id\n");
	printf("6) Address\n");
	printf("7) City\n");
	printf("8) State\n");
	printf("9)Country\n");
	printf("Enter your option(1-9): ");
	
	scanf("%d", &option);
	printf("Enter updated value of the specified field: ");
	getchar();//to empty the buffer.
	while((ch = getchar()) != '\n'){
		input[i++] = ch;
	}
	input[i] = '\0';
	switch(option){
		case 1:
			updateFirstName(con, userid, input);
			break;
		case 2:
			updateMiddleName(con, userid, input);
			break;
		case 3:
			updateLastName(con, userid, input);
			break;
		case 4:
			updateBranch(con, userid, input);
			break;
		case 5:
			updateEmail(con, userid, input);
			break;
		case 6:
			updateAddress(con, userid, input);
			break;
		case 7:
			updateCity(con, userid, input);
			break;
		case 8:
			updateState(con, userid, input);
			break;
		case 9:
			updateCountry(con, userid, input);
			break;
		default:
			printf("!!Invalid option!!\n");
	}
}
void transferMoney(MYSQL **con, int userid, int desUserid, int money){
	withdraw(con, userid, money);
	deposit(con, desUserid, money);
}
void deleteUser(MYSQL **con, int userid){
	char query[100];
	sprintf(query, "delete from customers_info where userid = %d;",userid);
	mysql_query(*con, query);
}

void updateFirstName(MYSQL **con, int userid, char *input){
	char query[100];
	sprintf(query, "update customers_info set first_name = '%s' where userid = %d;", input, userid);
	mysql_query(*con, query);
}

void updateMiddleName(MYSQL **con, int userid, char *input){
	char query[100];
	sprintf(query, "update customers_info set middle_name = '%s' where userid = %d;", input, userid);
	mysql_query(*con, query);
}

void updateLastName(MYSQL **con, int userid, char *input){
	char query[100];
	sprintf(query, "update customers_info set last_name = '%s' where userid = %d;", input, userid);
	mysql_query(*con, query);
}

void updateBranch(MYSQL **con, int userid, char *input){
	char query[100];
	sprintf(query, "update customers_info set branch = '%s' where userid = %d;", input, userid);
	mysql_query(*con, query);
}

void updateEmail(MYSQL **con, int userid, char *input){
	char query[100];
	sprintf(query, "update customers_info set email = '%s' where userid = %d;", input, userid);
	mysql_query(*con, query);
}

void updateAddress(MYSQL **con, int userid, char *input){
	char query[100];
	sprintf(query, "update customers_info set address = '%s' where userid = %d;", input, userid);
	mysql_query(*con, query);
}

void updateCity(MYSQL **con, int userid, char *input){
	char query[100];
	sprintf(query, "update customers_info set city = '%s' where userid = %d;", input, userid);
	mysql_query(*con, query);
}


void updateState(MYSQL **con, int userid, char *input){
	char query[100];
	sprintf(query, "update customers_info set state = '%s' where userid = %d;", input, userid);
	mysql_query(*con, query);
}

void updateCountry(MYSQL **con, int userid, char *input){
	char query[100];
	sprintf(query, "update customers_info set country = '%s' where userid = %d;", input, userid);
	mysql_query(*con, query);
}
