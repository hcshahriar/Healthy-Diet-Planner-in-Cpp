#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <limits>

using namespace std;

// Struct to store user information
struct UserInfo {
    string name;
    int age;
    char gender; // 'M' or 'F'
    double weight; // in kg
    double height; // in cm
    int activityLevel; // 1-5
};

// Struct to store food items
struct FoodItem {
    string name;
    int calories;
    double protein; // in grams
    double carbs;   // in grams
    double fats;    // in grams
};

// Struct to store meal plan
struct MealPlan {
    FoodItem breakfast;
    FoodItem lunch;
    FoodItem dinner;
    FoodItem snack;
};

// Function prototypes
void displayWelcome();
UserInfo getUserInfo();
double calculateBMI(const UserInfo& user);
int calculateDailyCalories(const UserInfo& user);
MealPlan generateMealPlan(int dailyCalories);
void displayResults(const UserInfo& user, double bmi, int calories, const MealPlan& plan);
void displayFoodItem(const FoodItem& item);
char getUpdateChoice();
void updateUserInfo(UserInfo& user);

int main() {
    char choice;
    
    do {
        displayWelcome();
        
        // Get user information
        UserInfo user = getUserInfo();
        
        // Calculate health metrics
        double bmi = calculateBMI(user);
        int dailyCalories = calculateDailyCalories(user);
        
        // Generate meal plan
        MealPlan plan = generateMealPlan(dailyCalories);
        
        // Display results
        displayResults(user, bmi, dailyCalories, plan);
        
        // Ask if user wants to update info
        choice = getUpdateChoice();
        if (choice == 'Y' || choice == 'y') {
            updateUserInfo(user);
            
            // Recalculate with updated info
            bmi = calculateBMI(user);
            dailyCalories = calculateDailyCalories(user);
            plan = generateMealPlan(dailyCalories);
            
            // Display updated results
            displayResults(user, bmi, dailyCalories, plan);
        }
        
        cout << "\nWould you like to start over with a new user? (Y/N): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
    } while (choice == 'Y' || choice == 'y');
    
    cout << "\nThank you for using the Healthy Diet Planner. Stay healthy!\n";
    
    return 0;
}

void displayWelcome() {
    cout << "============================================\n";
    cout << "       HEALTHY DIET PLANNER PROGRAM\n";
    cout << "============================================\n";
    cout << "This program will help you plan a healthy diet\n";
    cout << "based on your personal information and activity level.\n\n";
}

UserInfo getUserInfo() {
    UserInfo user;
    
    cout << "Please enter your information:\n";
    cout << "Name: ";
    getline(cin, user.name);
    
    cout << "Age: ";
    while (!(cin >> user.age) || user.age <= 0) {
        cout << "Please enter a valid age: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cout << "Gender (M/F): ";
    while (!(cin >> user.gender) || (toupper(user.gender) != 'M' && toupper(user.gender) != 'F')) {
        cout << "Please enter M or F: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    user.gender = toupper(user.gender);
    
    cout << "Weight (kg): ";
    while (!(cin >> user.weight) || user.weight <= 0) {
        cout << "Please enter a valid weight: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cout << "Height (cm): ";
    while (!(cin >> user.height) || user.height <= 0) {
        cout << "Please enter a valid height: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cout << "\nActivity Level:\n";
    cout << "1. Sedentary (little or no exercise)\n";
    cout << "2. Lightly active (light exercise 1-3 days/week)\n";
    cout << "3. Moderately active (moderate exercise 3-5 days/week)\n";
    cout << "4. Very active (hard exercise 6-7 days/week)\n";
    cout << "5. Extra active (very hard exercise & physical job)\n";
    cout << "Enter your activity level (1-5): ";
    
    while (!(cin >> user.activityLevel) || user.activityLevel < 1 || user.activityLevel > 5) {
        cout << "Please enter a number between 1 and 5: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return user;
}

double calculateBMI(const UserInfo& user) {
    // BMI formula: weight (kg) / (height (m))^2
    double heightInMeters = user.height / 100.0;
    return user.weight / (heightInMeters * heightInMeters);
}

int calculateDailyCalories(const UserInfo& user) {
    // Harris-Benedict equation for BMR
    double bmr;
    if (user.gender == 'M') {
        bmr = 88.362 + (13.397 * user.weight) + (4.799 * user.height) - (5.677 * user.age);
    } else {
        bmr = 447.593 + (9.247 * user.weight) + (3.098 * user.height) - (4.330 * user.age);
    }
    
    // Adjust for activity level
    double activityFactor;
    switch (user.activityLevel) {
        case 1: activityFactor = 1.2; break;    // Sedentary
        case 2: activityFactor = 1.375; break;  // Lightly active
        case 3: activityFactor = 1.55; break;   // Moderately active
        case 4: activityFactor = 1.725; break;  // Very active
        case 5: activityFactor = 1.9; break;    // Extra active
        default: activityFactor = 1.2;
    }
    
    return static_cast<int>(round(bmr * activityFactor));
}

MealPlan generateMealPlan(int dailyCalories) {
    // Define some healthy food options
    const int NUM_OPTIONS = 3;
    FoodItem breakfastOptions[NUM_OPTIONS] = {
        {"Oatmeal with berries and nuts", 350, 10, 50, 12},
        {"Greek yogurt with honey and granola", 300, 20, 35, 8},
        {"Avocado toast with eggs", 400, 15, 35, 20}
    };
    
    FoodItem lunchOptions[NUM_OPTIONS] = {
        {"Grilled chicken salad", 450, 35, 20, 25},
        {"Quinoa bowl with vegetables", 400, 15, 60, 12},
        {"Salmon with sweet potato", 500, 30, 45, 20}
    };
    
    FoodItem dinnerOptions[NUM_OPTIONS] = {
        {"Grilled fish with vegetables", 450, 35, 20, 20},
        {"Turkey breast with brown rice", 500, 40, 45, 15},
        {"Tofu stir-fry with quinoa", 400, 20, 50, 12}
    };
    
    FoodItem snackOptions[NUM_OPTIONS] = {
        {"Handful of almonds", 200, 6, 6, 16},
        {"Apple with peanut butter", 250, 5, 30, 12},
        {"Protein smoothie", 300, 20, 30, 8}
    };
    
    // Select options based on calorie needs (simplified logic)
    int selection = 0;
    if (dailyCalories < 1800) selection = 0; // Lower calorie options
    else if (dailyCalories < 2200) selection = 1;
    else selection = 2; // Higher calorie options
    
    MealPlan plan;
    plan.breakfast = breakfastOptions[selection];
    plan.lunch = lunchOptions[selection];
    plan.dinner = dinnerOptions[selection];
    plan.snack = snackOptions[selection];
    
    // Adjust portion sizes based on exact calorie needs
    double calorieFactor = static_cast<double>(dailyCalories) / 1800.0;
    
    auto adjustItem = [calorieFactor](FoodItem item) {
        item.calories = static_cast<int>(round(item.calories * calorieFactor));
        item.protein = round(item.protein * calorieFactor * 10) / 10;
        item.carbs = round(item.carbs * calorieFactor * 10) / 10;
        item.fats = round(item.fats * calorieFactor * 10) / 10;
        return item;
    };
    
    plan.breakfast = adjustItem(plan.breakfast);
    plan.lunch = adjustItem(plan.lunch);
    plan.dinner = adjustItem(plan.dinner);
    plan.snack = adjustItem(plan.snack);
    
    return plan;
}

void displayResults(const UserInfo& user, double bmi, int calories, const MealPlan& plan) {
    cout << fixed << setprecision(1);
    cout << "\n\n============================================\n";
    cout << "          HEALTHY DIET PLAN FOR " << user.name << "\n";
    cout << "============================================\n";
    
    // Display user stats
    cout << "\nYOUR STATS:\n";
    cout << "Age: " << user.age << " years\n";
    cout << "Gender: " << (user.gender == 'M' ? "Male" : "Female") << "\n";
    cout << "Weight: " << user.weight << " kg\n";
    cout << "Height: " << user.height << " cm\n";
    
    string activityStr;
    switch (user.activityLevel) {
        case 1: activityStr = "Sedentary"; break;
        case 2: activityStr = "Lightly active"; break;
        case 3: activityStr = "Moderately active"; break;
        case 4: activityStr = "Very active"; break;
        case 5: activityStr = "Extra active"; break;
        default: activityStr = "Unknown";
    }
    cout << "Activity Level: " << activityStr << "\n";
    
    // Display BMI and interpretation
    cout << "\nBMI: " << bmi << " - ";
    if (bmi < 18.5) {
        cout << "Underweight";
    } else if (bmi < 25) {
        cout << "Normal weight";
    } else if (bmi < 30) {
        cout << "Overweight";
    } else {
        cout << "Obese";
    }
    cout << "\n";
    
    // Display daily calorie needs
    cout << "\nEstimated Daily Calorie Needs: " << calories << " kcal\n";
    
    // Display meal plan
    cout << "\nRECOMMENDED MEAL PLAN:\n";
    cout << "----------------------\n";
    
    cout << "\nBREAKFAST:\n";
    displayFoodItem(plan.breakfast);
    
    cout << "\nLUNCH:\n";
    displayFoodItem(plan.lunch);
    
    cout << "\nDINNER:\n";
    displayFoodItem(plan.dinner);
    
    cout << "\nSNACK:\n";
    displayFoodItem(plan.snack);
    
    // Calculate total nutrition
    int totalCalories = plan.breakfast.calories + plan.lunch.calories + 
                        plan.dinner.calories + plan.snack.calories;
    double totalProtein = plan.breakfast.protein + plan.lunch.protein + 
                          plan.dinner.protein + plan.snack.protein;
    double totalCarbs = plan.breakfast.carbs + plan.lunch.carbs + 
                        plan.dinner.carbs + plan.snack.carbs;
    double totalFats = plan.breakfast.fats + plan.lunch.fats + 
                       plan.dinner.fats + plan.snack.fats;
    
    cout << "\nTOTAL DAILY NUTRITION:\n";
    cout << "Calories: " << totalCalories << " kcal\n";
    cout << "Protein: " << totalProtein << " g\n";
    cout << "Carbohydrates: " << totalCarbs << " g\n";
    cout << "Fats: " << totalFats << " g\n";
}

void displayFoodItem(const FoodItem& item) {
    cout << item.name << "\n";
    cout << "  Calories: " << item.calories << " kcal\n";
    cout << "  Protein: " << item.protein << " g\n";
    cout << "  Carbs: " << item.carbs << " g\n";
    cout << "  Fats: " << item.fats << " g\n";
}

char getUpdateChoice() {
    char choice;
    cout << "\nWould you like to update your information and recalculate? (Y/N): ";
    while (!(cin >> choice) || (toupper(choice) != 'Y' && toupper(choice) != 'N')) {
        cout << "Please enter Y or N: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

void updateUserInfo(UserInfo& user) {
    cout << "\nCURRENT INFORMATION:\n";
    cout << "1. Name: " << user.name << "\n";
    cout << "2. Age: " << user.age << "\n";
    cout << "3. Gender: " << user.gender << "\n";
    cout << "4. Weight: " << user.weight << " kg\n";
    cout << "5. Height: " << user.height << " cm\n";
    cout << "6. Activity Level: " << user.activityLevel << "\n";
    
    cout << "\nEnter the number of the field you want to update (1-6, or 0 to cancel): ";
    int choice;
    while (!(cin >> choice) || choice < 0 || choice > 6) {
        cout << "Please enter a number between 0 and 6: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    if (choice == 0) return;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch (choice) {
        case 1:
            cout << "Enter new name: ";
            getline(cin, user.name);
            break;
        case 2:
            cout << "Enter new age: ";
            while (!(cin >> user.age) || user.age <= 0) {
                cout << "Please enter a valid age: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            break;
        case 3:
            cout << "Enter new gender (M/F): ";
            while (!(cin >> user.gender) || (toupper(user.gender) != 'M' && toupper(user.gender) != 'F')) {
                cout << "Please enter M or F: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            user.gender = toupper(user.gender);
            break;
        case 4:
            cout << "Enter new weight (kg): ";
            while (!(cin >> user.weight) || user.weight <= 0) {
                cout << "Please enter a valid weight: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            break;
        case 5:
            cout << "Enter new height (cm): ";
            while (!(cin >> user.height) || user.height <= 0) {
                cout << "Please enter a valid height: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            break;
        case 6:
            cout << "\nActivity Level:\n";
            cout << "1. Sedentary (little or no exercise)\n";
            cout << "2. Lightly active (light exercise 1-3 days/week)\n";
            cout << "3. Moderately active (moderate exercise 3-5 days/week)\n";
            cout << "4. Very active (hard exercise 6-7 days/week)\n";
            cout << "5. Extra active (very hard exercise & physical job)\n";
            cout << "Enter new activity level (1-5): ";
            
            while (!(cin >> user.activityLevel) || user.activityLevel < 1 || user.activityLevel > 5) {
                cout << "Please enter a number between 1 and 5: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            break;
    }
    
    cout << "Information updated successfully!\n";
}
