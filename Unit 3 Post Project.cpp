// Kris Bicknell
// March 5, 2024
// Unit 3 Post Project
// Another even more involved payment system, because apparently my work must never be complete.

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

string userName,userAddress;
int paintCanStock = 8, paintBrushStock = 16, paintRollerStock = 4, paintCanNum, paintBrushNum, paintRollerNum;
double paintCanCost = 10.99, paintBrushCost = 3.99, paintRollerCost = 6.99, taxRate=0.05, creditCharge=0.15, cashDisc=0.07, userSpend;
double subtotal, total, taxAmount, creditAmount, costPerItem, discAmount, itemAverage;
int payMethod, rewardLevel;

//Variables for shipping calculations

double paintCanWeight = 192.0, paintBrushWeight = 0.4, paintRollerWeight = 32.0;
double distCost = 0.45, weightConvert = 16.0, shippingPerLb=2.65,userDist,totalWeight,distAmount,weightAmount,shippingTotal;

int main()
{
    cout << fixed << setprecision(2);
    cout << "Welcome to The Store!\n";
    cout << "We currently have the following in stock:\n\n";
    cout << paintCanStock << " cans of paint for $" << paintCanCost << endl;
    cout << paintBrushStock << " paint brushes for $" << paintBrushCost << endl;
    cout << paintRollerStock << " paint rollers for $" << paintRollerCost << endl;

    //User name and reward level is calculated
    cout << "Please enter the name for this order: ";
    getline(cin, userName);//no cin.ignore needed, since this is the first user input
    cout << "\nHow much have you previously spent at The Store? ";
    cin >> userSpend;
    cout << endl;
    if (userSpend < 0)//Validates that input was positive
    {
        cout << "Invalid input. Number cannot be negative. Please restart the program.";
        return 0;
    }
    if (userSpend <= 100)
    {
        rewardLevel = 1;
        cout << "You are currently a Bronze member. You need to spend $" << (101 - userSpend) << " to reach Silver level.";
    }
    else if (userSpend >= 101 && userSpend < 200)
    {
        rewardLevel = 2;
        cout << "You are currently a Silver member. You need to spend $" << (200 - userSpend) << " to reach Gold level.";
    }
    else if (userSpend >= 200)
    {
        rewardLevel = 3;
        cout << "You are currently a Gold member. All financing fees will be waived on your order!";
    }
    else
    {
        cout << "Invalid input. Please restart the program.";
        return 0;
    }

    //User input what they're buying
    cout << endl << "How many cans of paint would you like to buy? ";
    cin >> paintCanNum;
    if (paintCanNum > paintCanStock)
    {
        paintCanNum = paintCanStock;
        cout << endl << "Oops, you can't buy that many! Automatically rounded down to " << paintCanNum << ".";//reads out the actual paint can number instead of stock, allows me to see that it mathed correctly
    }
    cout << endl << "How many paint brushes would you like to buy? ";
    cin >> paintBrushNum;
    if (paintBrushNum > paintBrushStock)
    {
        paintBrushNum = paintBrushStock;
        cout << endl << "Oops, you can't buy that many! Automatically rounded down to " << paintBrushNum << ".";
    }
    cout << endl << "How many paint rollers would you like to buy? ";
    cin >> paintRollerNum;
    if (paintRollerNum > paintRollerStock)
    {
        paintRollerNum = paintRollerStock;
        cout << endl << "Oops, you can't buy that many! Automatically rounded down to " << paintRollerNum << ".";
    }

    //Choose payment method
    cout << "\n\nHow would you like to pay for your order?\nEnter 1 for Cash (7% discount)\nEnter 2 for Card (15% financing charge)\nEnter 3 for Web (15% financing plus shipping)\n";
    cin >> payMethod;
    cout << endl;
    subtotal = (paintCanNum * paintCanCost) + (paintBrushNum * paintBrushCost) + (paintRollerNum * paintRollerCost);//same for every option so why repeat it
    switch (payMethod)
    {
    case 1://Cash
    {
        cout << "----------------CASH BILL----------------" << endl;
        cout << "Customer name: " << userName << endl;
        cout << "SUBTOTAL:" << setw(32) << right << subtotal << endl;
        discAmount = (subtotal * cashDisc);
        cout << left << "DISCOUNT:" << setw(32) << right << discAmount << endl;
        taxAmount = (subtotal * taxRate);
        cout << "TAX:" << setw(37) << right << taxAmount << endl;
        total = subtotal + taxAmount - cashDisc;
        cout << "TOTAL:" << setw(35) << right << total << endl;
        itemAverage = (total / (paintCanNum + paintBrushNum + paintRollerNum));
        cout << "AVERAGE PER ITEM:" << setw(24) << right << itemAverage << endl;
        break;
    }
    case 2://Card
    {
        cout << "----------------CARD BILL----------------\n";
        if (rewardLevel == 3)
        {
            cout << "As a Gold member, all financing fees are waived. You'll just pay for your items plus tax." << endl;
            cout << "Gold Customer name: " << userName << endl;
        }
        else
        {
            cout << "Customer name: " << userName << endl;
        }
        cout << "SUBTOTAL:" << setw(32) << right << subtotal << endl;
        if (rewardLevel != 3)
        {
            creditAmount = (subtotal * creditCharge);

        }
        cout << "CARD CHARGE:" << setw(29) << right << creditAmount << endl;
        taxAmount = (subtotal * taxRate);
        cout << "TAX:" << setw(37) << right << taxAmount << endl;
        total = subtotal + taxAmount + creditAmount;
        cout << "TOTAL:" << setw(35) << right << total << endl;
        itemAverage = (total / (paintCanNum + paintBrushNum + paintRollerNum));
        cout << "AVERAGE PER ITEM:" << setw(24) << right << itemAverage << endl;
        break;
    }
    case 3://Web order, display card bill THEN shipping bill. I feel like this would've benefitted from being stuck into the card bill application so there's less repeated code, but what do I know
    {  
        cout << "What is your shipping address? ";
        cin.ignore(1);
        getline(cin, userAddress);
        cout << endl << "How many miles is this address from our store? ";
        cin >> userDist;
        cout << endl << endl;
        //card bill
        cout << "----------------CARD BILL----------------\n";
        if (rewardLevel == 3)
        {
            cout << "As a Gold member, all financing fees are waived. You'll just pay for your items plus tax." << endl;
            cout << "Gold Customer name: " << userName << endl;
        }
        else
        {
            cout << "Customer name: " << userName << endl;
        }
        cout << "SUBTOTAL:" << setw(32) << right << subtotal << endl;
        if (rewardLevel != 3)
        {
            creditAmount = (subtotal * creditCharge);

        }
        cout << "CARD CHARGE:" << setw(29) << right << creditAmount << endl;
        taxAmount = (subtotal * taxRate);
        cout << "TAX:" << setw(37) << right << taxAmount << endl;
        total = subtotal + taxAmount + creditAmount;
        cout << "TOTAL:" << setw(35) << right << total << endl;
        itemAverage = (total / (paintCanNum + paintBrushNum + paintRollerNum));
        cout << "AVERAGE PER ITEM:" << setw(24) << right << itemAverage << endl;
        //shipping bill
        cout << endl << "--------------SHIPPING BILL--------------\n";
        cout << "Customer name: " << userName << endl;
        cout << "Shipping to: " << userAddress << endl << endl;
        distAmount = (userDist * distCost);
        cout << "MILEAGE COST:" << setw(28) << right << distAmount<<endl;
        totalWeight = ((paintCanNum * paintCanWeight) + (paintBrushNum * paintBrushWeight) + (paintRollerNum * paintRollerWeight));
        weightAmount = ceil(weightConvert * totalWeight);
        weightAmount *= shippingPerLb;
        cout << "WEIGHT COST:" << setw(29) << right << weightAmount<<endl;
        shippingTotal = (weightAmount + distAmount);
        cout << "SHIPPING TOTAL:" << setw(26) << right << shippingTotal<<endl<<endl;
        total += shippingTotal;
        cout << "ONLINE ORDER TOTAL:" << setw(22) << right << total << endl;
        
        break;
    }
    default:
        cout << "Invalid payment method. Please restart the program.";
        return 0;
    }
    //Determine if user has reached a new reward level
    userSpend += total;
    cout << "NEW TOTAL SPENT:" << setw(25)<<right << userSpend << endl<<endl;
    switch (rewardLevel)
    {
    case 1:
        if (userSpend <= 100)
        {
            cout << "You are currently a Bronze member. You need to spend $" << (101 - userSpend) << " to reach Silver level.";
        }
        else if (userSpend >= 101 && userSpend < 200)
        {
            rewardLevel = 2;
            cout << "Congratulations, you are now a Silver member!";
        }
        else if (userSpend >= 200)
        {
            rewardLevel = 3;
            cout << "Congratulations, you are now a Gold member! All financing fees will be waived on your future orders!";
        }
        else
        {
            cout << "Invalid input. Please restart the program.";
            return 0;
        }
        break;
    case 2:
        if (userSpend >= 101 && userSpend < 200)
        {
            cout << "You are currently a Silver member. You need to spend $" << (200 - userSpend) << " to reach Gold level and have all financing fees waived.";
        }
        else if (userSpend >= 200)
        {
            rewardLevel = 3;
            cout << "Congratulations, you are now a Gold member! All financing fees will be waived on your future orders!";
        }
        else
        {
            cout << "Invalid input. Please restart the program.";
            return 0;
        }
        break;
    }

    return 0;
}