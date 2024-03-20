#define CONFIG_H

//constants
#define MAX_CATEGORIES 12
#define MAX_TITLE_LEN 150
#define MAX_NAME_LEN 15

//main 
#define INPUT_TITLE "Enter title of bar chart: "
#define INPUT_NUMCAT "Enter number of categories: "
#define INPUT_CATNAME "Enter category name: "
#define INPUT_CATQUANTITY "Enter category quantity: "
#define INPUT_LABELX "Enter label for x-axis: "
#define INPUT_SORT "Sort by (a) category name or (b) bar length? "

//prompts
#define MAIN_PRINT "1. Print Chart\n2. Edit Chart\n3. New Chart\n4. Export Chart\n5. Exit\n\nEnter option: "
#define EDIT_VALUES "\n1. Change category name \n2. Change category quantity \n3. Add new category \n4. Remove category\nSelect one of the options above: "
#define ENTER_CATNAME "Enter category name: "
#define ENTER_CATQUANTITY "Enter category quantity: "
#define ENTER_CATREMOVE "\nEnter Index of item to remove: "
#define ENTER_CATINDEX "\nEnter Index of item to edit: "

//error messages
#define CATNAME_EXISTS "Category name already exists. Please enter a different name: "
#define CATNAME_LONG "Category name is too long. Please enter a shorter name: "
#define INVALID_INPUT "Invalid input. Please enter a valid input:\n"
#define INVALID_NEGATIVE "Invalid input. Please enter a positive number:\n"
#define INVLAID_MAX "MAX Categories reached, remove some before adding.\n"
#define FILE_ERROR "Error opening file for writing.\n"
#define INVALID_RANGE "Input error. Please enter a valid integer between 1 and "

//configurations
#define FILE_PATH "graph.txt"

//success msgs
#define SUCCESS_SAVE "Chart saved to file.\n"
