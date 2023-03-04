#include "mysqlFunc.h"

static char *host = "localhost";//this is the ip address of the machine where database is present                  
static char *user = "root";
static char *pass = "PetronesTower1.";
static char *dbname = "bankManagmentSys";
unsigned int port = 3306;
static char *unix_socket = NULL;
unsigned int conFlag = 0;
int main(){
	int customer_type;//existing customer - 1; new customer - 2
	int valid = 1; //when invalid then set to 1; when valid then set to 0
	int userid;
	char password[50];
	char firstName[50], middleName[50], LastName[50];
	long long int phoneNo;
	char address[100],city[50], state[50], country[50], branch[50];
	char email[50];
	int option = 0;
	int depositAmount;
	int withdrawAmount;
	int desUserid, transMoney;
	int i = 0;
	char ch;
	MYSQL *con;
	con = mysql_init(NULL);
	if(mysql_real_connect(con, host, user, pass, dbname, port, unix_socket, conFlag)){
		printf("Connection succesful\n");
	}
	else{
		printf("Error %s %d", mysql_error(con), mysql_errno(con));
		return 1;
	}
	while(true){
		printf("----Welcome to COEP Bank----\n");
		printf("----Login----\n");
		printf("Enter 1 for existing customer:-\n");
		printf("Enter 2 for new customer:-\n");
		printf("Enter your option: ");
		scanf("%d", &customer_type);
		valid = 1;
		if(customer_type == 1){
			while(valid){
				printf("Enter userid: ");
				scanf("%d", &userid);
				printf("Enter password: ");
				scanf("%s", password);
				if(isValidUserid(&con, userid)){
					while(valid){
						if(isValidPassword(&con, userid, password)){
							valid = 0;// Getting out of the while loop
							printf("Login Successful.\n");
						}
						else{
							printf("!!!!Wrong password!!!!\n");
							printf("Please try again.\n");
							printf("Enter password: ");
							scanf("%s", password);
						}
					}
				}
				else{
					printf("!!!!Invalid userid!!!!\n");
					printf("Please try again.\n");
				}
			}
			option = 0;
			while(option != 8){
				printf("----Menu----\n");
				printf("1)Deposit\n");
				printf("2)Withdrawal\n");
				printf("3)Check Balance\n");
				printf("4)View Profile\n");
				printf("5)Update Profile\n");
				printf("6)Money Transfer\n");
				printf("7)Close Account\n");
				printf("8)Log out\n");
				printf("Enter your option: ");
				scanf("%d", &option);
				switch(option){
					case 1:
						printf("Your account balance: Rs %d\n", getBalance(&con, userid));
						printf("Enter amount: ");
						scanf("%d", &depositAmount);
						deposit(&con, userid, depositAmount);
						printf("Your account balance: Rs %d\n", getBalance(&con, userid));
						break;
					case 2:
						printf("Your account balance : Rs %d\n", getBalance(&con, userid));
						printf("Enter withdrawal amount: ");
						scanf("%d", &withdrawAmount);
						if(isWithdrawalPossible(&con, userid, withdrawAmount)){
							withdraw(&con, userid, withdrawAmount);
							printf("Your account balance : Rs %d\n", getBalance(&con, userid));
						}
						else{
							printf("!!Withdrawal not possible!!\n");
						}
						break;
					case 3:
						printf("Your account balance : Rs %d\n", getBalance(&con, userid));
						break;
					case 4:
						printProfile(&con, userid);
						break;
					case 5:
						updateProfile(&con, userid);
						break;
					case 6:
						printf("Your account balance : Rs %d\n", getBalance(&con, userid));
						printf("Enter userid of the destination account: ");
						scanf("%d", &desUserid);
						printf("Enter amount to be transfered: ");
						scanf("%d", &transMoney);
						if(isWithdrawalPossible(&con, userid, transMoney)){
							if(isValidUserid(&con, desUserid)){
								transferMoney(&con, userid, desUserid, transMoney);
								printf("Money transferred successfully");
								printf("Your account balance : Rs %d\n", getBalance(&con, userid));
							}
							else{
								printf("!!Invalid destination userid!!");
							}
						}
						else{
							printf("!!Transaction could not be carried out!!\nNot enough balance in your account.\n");
						}
						break;

					case 7:
						printf("Closing account...\n");
						deleteUser(&con, userid);
						printf("Account closed.\n");
						option = 8;
						break;
					case 8:
						break;
					default:
						printf("!!Invalid option!!\n");
						printf("Please try again.\n");
						break;
				}
			}
		}
		else if(customer_type == 2){
			printf("Enter userid (8 digit only numeric): ");
			scanf("%d", &userid);
			printf("Enter your first name: ");
			scanf("%s", firstName);
			printf("Enter your middle name: ");
			scanf("%s", middleName);
			printf("Enter your last name: ");
			scanf("%s", LastName);
			printf("Enter your phone no: ");
			scanf("%lld", &phoneNo);
			printf("Enter your address: ");
			getchar();// to empty the buffer.
			while((ch = getchar()) != '\n'){
				address[i++] = ch;
			}
			address[i] = '\0';	
			printf("Enter your email id: ");
			scanf("%s", email);
			printf("Enter City: ");
			scanf("%s", city);
			printf("Enter State: ");
			scanf("%s", state);
			printf("Enter Country: ");
			scanf("%s", country);
			printf("Enter your preffered branch: ");
			scanf("%s", branch);
			printf("Enter password: ");
			scanf("%s", password);
			insertUser(&con, userid, password, firstName, middleName, LastName, phoneNo, email, address, city, state, country, branch);
			printf("Account added successfully.\n");
			printf("Login to use the services.\n");
		}
		else{
			printf("!!!!Invalid option!!!!\n");
			printf("Please try again");
		}
	}
	mysql_close(con);
	return 0;
}
