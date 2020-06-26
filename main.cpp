// Created by JOSHUA DANIEL MUKIIBI 2345825 on 5/26/2020.
// If you wish to read more into how this came to be I advise starting by looking at the Resources class, then Grid then Archaeologist then come back here
// It will flow better that way as it is how I built it.

#include "Archaeologist.h"
#include <windows.h>

int main()
{
    srand(time(nullptr));
    int board_size;
    cout << "Welcome to THE BONE WARS!!\nEnter size of island you'd like to search on!!" << endl;
    cout << "Enter size: ";
    cin >> board_size;
    Grid *Island = new Grid(board_size);
    Island->deploy_resources();
    //Calculate the energy for the players
    int maxi = 2*board_size;
    int energy = rand()%(maxi-board_size+1)+board_size;
    //After calculating the energy we then now create our players.
    auto *player1 = new Archaeologist(Island, "Cope", energy);
    auto *player2 = new Archaeologist(Island, "Marsh", energy);
    cout << "One of you will play as Cope and the other as Marsh, famous archaeologists on a quest to see who finds more bones." << endl;
    cout << "Instructions, Map Key and Gameplay Explanation:\n---------------------------------------------" << endl;
    cout << "'X' - means not discovered coordinate.\n";
    cout << "'D' - means discovered coordinate.\n";
    cout << "'F' - Bone (Full Body) worth +100 bone score\n";
    cout << "'S' - Bone (Skull) worth +50 bone score\n";
    cout << "'O' - Bone (Ordinary) worth +20 bone score\n";
    cout << "'B' - Food Burger gives +4 energy\n";
    cout << "'N' - Food Nuggets give +3 energy\n";
    cout << "'C' - Food Chips give +2 energy\n";
    cout << "'W' - Water gives +1 energy\n";
    cout << "'M' - Medkits nullify any trap effects\n";
    cout << "'T' - Traps lead to energy reduction per turn\n";
    cout << "1.Enter coordinates starting from 0 to the 1 less than the board size you chose. So for example if it was 5, the highest single point is 4\n";
    cout << "2.Choose amongst yourselves who goes first.\n";
    cout << "Then the first person is to choose coordinate [0][0] the next person [" << board_size-1 << "]" << "[" << board_size-1 << "]\n";
    cout << "From then on it's all your choice. Apologies for making you have to do that but what can I do. Developer's Dilemma xD" << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << "Total Bone Score to Win Game: " << Island->getbone_score() << endl;
    cout << player1->getname() << " Energy: " << player1->getenergy() << endl;
    cout << player2->getname() << " Energy: " << player2->getenergy() << endl;
    Sleep(5000);
    cout << "Ready to conquer the Island! Here We Go!" << endl;
    Sleep(3000);
    fflush(stdin);
    int round = 1;
    int break_point = Island->getbone_score()/2;
    int flag_winner;
    while (player1->getenergy() >= 0 || player2->getenergy() >= 0)
    {
        flag_winner = -1;//random sentinel value.
        cout << "--------------------------------------------------------" << endl;
        cout << "Round " << round << ":" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << endl << "The Island" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << *Island;
        if(player1->getenergy()==0)//when energy is 0 you're still able to win but you can't play
            cout << "Sorry about your untimely death " << player1->getname() << "! Hopefully you had collected the most bones already!" << endl;
        else
        {
            player1->play_turn();
            cout << player1->getname() << " has played his turn! Let's see how things stack up!" << endl;
            cout << "--------------------------------------------------------" << endl;
            player1->energy_calculator();
            cout << "Energy: " << player1->getenergy() << endl;
            cout << "BoneScore: " << player1->getbone_score() << endl;
            player1->getcondition();
        }
        cout << "And Now let's see how the Island has changed as well!" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << *Island;

        if(player2->getenergy()==0)
            cout << "Sorry about your untimely death " << player2->getname() << "! Hopefully you had collected the most bones already!" << endl;
        else
        {
            player2->play_turn();
            cout << player2->getname() << " has played his turn! Let's see how things stack up!" << endl;
            cout << "--------------------------------------------------------" << endl;
            player2->energy_calculator();
            cout << "Energy: " << player2->getenergy() << endl;
            cout << "BoneScore: " << player2->getbone_score() << endl;
            player2->getcondition();
        }
        cout << "And now A Final Look at our Island before the next round" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << *Island;
        round++;
        if(player1->getbone_score() > break_point)
        {
            flag_winner = 1;
            break;
        }
        else if(player2->getbone_score() > break_point)
        {
            flag_winner = 0;
            break;
        }
        else
            continue;
    }
    if(flag_winner==1)
        cout << "\nCongratulations " << player1->getname() << "! You have conquered the Island and bested your best friend and foe!" << endl;
    else
        cout << "\nCongratulations " << player2->getname() << "! You have conquered the Island and bested your best friend and foe!" << endl;
    cout << "Final Bone Scores:\n";
    cout << "--------------------------------------------------------" << endl;
    cout << player1->getname() << ": " << player1->getbone_score() << endl;
    cout << player2->getname() << ": " << player2->getbone_score() << endl;
    cout << "See you next time great adventurers for more discovery!!\nI promise the next time I will have a more challenging Island for you!" << endl;
    cout << "Au revoir and Safe travels back home!" << endl;
    delete Island;
    delete player1;
    delete player2;
    return 0;
}
