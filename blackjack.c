/**
 * Author:       David Nadeau 4515649
 * Purpose:      Create blackjack using C
 * Instructions: Run ./blackjack and follow given instructions
 * Syntax:       Variables prefixed with i are indexes for arrays
 *               Variables prefixed with n are used for counts
 * */

#include <stdio.h>

int player_hand[10];  //players hand
int house_hand[10];  //house hand
int deck[52];       //starting deck

int busted = 0;   //used to indicate if the player has busted

/** card handleling methods */
void qsort(int *,int,int);   //quicksort i found online. used to count aces last when tallying scores
int  tally_hand(int *);     //counts total score of given hand
int  count_cards(int *);   //counts number of cards in an array
int  get_value(int);      //gets value from card, face =10...etc
int  get_new_card();     //gets a new card ensuring no duplicates
void clear_hand(int *); //sets all elements in array to -1 (to not be confused with 0 AC)
void load_deck();      //put numbers 0-51 in the deck
void shuffle_deck();  //shuffle the deck
char get_suite(int); //return suite
char get_rank(int); //return rank

/** printing methods */
void print_hand(int *, char *);//prints an array with custom text
void show_welcome();          //ascii art welcome msg

/** game logic methods */
void initial_deal();        //deal 1 card to house and 2 to player
void player_loop();        //handles all the player logic
void house_loop();        //handles all the house logic
void judgement();        //tallies scores and sees who one
/*
---------------------------------------------------
 *  Methods dealing with preparing/tallying of cards.
----------------------------------------------------
*/
int tally_hand(int *hand)
{
    qsort (hand,0,count_cards(hand)-1); //quick sort to get ace in the front
    int ncards, i, score, card_value;
    score = 0;
    ncards = count_cards(hand);
    for (i = ncards-1; i >= 0; --i) //count down so ace is last card read. easier to judge 11 vs 1.
    {
        card_value = get_value(hand[i]);
        if (card_value == -1)
            if ((score + 11) > 21)
                ++score;
            else
                score += 11;
        else
            score += card_value;
    }
    return score;
}
int count_cards(int *hand)
{
    int ncards;
    for (ncards = 0; hand[ncards] != -1; ++ncards)
    ;
    return ncards;
}
void clear_hand(int *hand)
{
    int i;
    for (i = 0; i < 10; ++i)
        hand[i] = -1;
}
void load_deck()
{
    int i;
    for (i = 0; i < 52; ++i)
        deck[i]=i;
}
void shuffle_deck()
{
    int ntimes, firstcard, secondcard, tempcard;
    ntimes = firstcard = secondcard = tempcard = 0;

    //loop random amount between 100 and 199
    for (ntimes = (99 + rand() % 100); ntimes > 0; --ntimes)
    {
        //get 2 random cards
        firstcard = rand() % 52;
        secondcard = rand() % 52;
        //swap cards using temp var
        tempcard = deck[firstcard];
        deck[firstcard] = deck[secondcard];
        deck[secondcard] = tempcard;
    }
}
char get_suite(int card)
{
    if (card < 13)
        return 'C';
    else if (card < 26)
        return 'D';
    else if (card < 39)
        return 'H';
    else if (card < 52)
        return 'S';
    else
        return ' ';
}
char get_rank(int card)
{
    int c;
    c = card % 13;
    switch (c)
    {
        case 0:
            return 'A';
        case 1:
            return '2';
        case 2:
            return '3';
        case 3:
            return '4';
        case 4:
            return '5';
        case 5:
            return '6';
        case 6:
            return '7';
        case 7:
            return '8';
        case 8:
            return '9';
        case 9:
            return 'T';
        case 10:
            return 'J';
        case 11:
            return 'Q';
        case 12:
            return 'K';
    }
}
int get_value(int card)
{
    int c;
    c = card % 13;
    if (c == 0)
        return -1;
    else if (c < 10)
        return c+1;
    else
        return 10;
}
int get_new_card()
{
    int card_index, new_card;
    card_index = new_card = 0;
    while (1)
    {
        card_index = rand() % 52;
        if (deck[card_index] != -1)
        {
            new_card = deck[card_index];
            deck[card_index] = -1;
            return new_card;
        }
    }
}
void qsort(int a[], int lo, int hi)
{
  int h, l, p, t;

  if (lo < hi) {
    l = lo;
    h = hi;
    p = a[hi];

    do {
      while ((l < h) && (a[l] <= p))
          l = l+1;
      while ((h > l) && (a[h] >= p))
          h = h-1;
      if (l < h) {
          t = a[l];
          a[l] = a[h];
          a[h] = t;
      }
    } while (l < h);

    a[hi] = a[l];
    a[l] = p;

    qsort( a, lo, l-1 );
    qsort( a, l+1, hi );
  }
}

/*
---------------------------------------------------
 *  Methods dealing with printing info to console
----------------------------------------------------
*/
void show_welcome()
{
    printf("                     ....,........           ..,...,+..,:.....                   \n");
    printf("                .  .,,............           .,..N.N.......,,,....               \n");
    printf("              ..,... ..............          ,..D,M............:,.               \n");
    printf("        ...,......................,..     ......?7=................:,....        \n");
    printf("..  .,,. .............,..........David Nadeau...:O........,............,:,....   \n");
    printf("... ...  .,..........,........,....,.      ,...=M....+N....8M=.............,,.   \n");
    printf(":....+...............,......,.........   ..,.N.8...O88D=...:8DOD8.............~, \n");
    printf("......+.............,......,........,.  ..:..,.......~OO..,Z$ZNMN8DN?..........+ \n");
    printf("......M...................,.......Blackjack..........I=.,.7$$$Z$~..M7...D.......,\n");
    printf("? .M..I?...........M.... ............,. .~........,..,.77D$7D$........?I.......Z \n");
    printf("+  .,.....,........MM.................. ,.......$+8=DD?DDZOZ8$....=..7?.......~I \n");
    printf("~?.................NMN7.,.............,.,.......DZONDND8NO8MD..,=...,$8.......$= \n");
    printf(",+7D..............:NNNNDN..............,.......O+DOND8NDD88DDONMO..?$$.......O+, \n");
    printf(".~= ..............NNNDDDDDD88.................~DN8OMNNDN8MMMNMZN88.??....... I:. \n");
    printf(".,? .............NDNDDDDD88888OZ......:.......M8~7O+M:.IMNDN$DMMNMDM........O~.  \n");
    printf("..=+............INDDDDD888888OOOZ....,......,NZNN7=NDMD:M77NMMMM?MNN.......=I,   \n");
    printf(" .:+..........,IDDDDD888888OOOOOZZ...........78ZD=,7NDO8ODMD8M7MZ=MNZ......$~.   \n");
    printf(" .,~?.........:DDDDD88888OOOOOZZZZ..,.......IOMOMDIM7M7OMONM+NZM?,+D......O+,    \n");
    printf("  .,+.........DDD88888O8O8OOZZZZZZ.........MNDM+MO8NZM$NONNNIMNMO78:......?:.    \n");
    printf("  ..~~........8888888OOO$7OZZZZ$I..:.......OM:+MMMMMNN.MMMO7$M=M=+$....,.O~.     \n");
    printf("  ..,?........D8888OOOO7,I,,.:  ..:.........8D+MMM87INI.MM:8MM.8MI......?I,.     \n");
    printf("  ...==........8OO8OZZ$..Z$,..............$?7OMNN7I8MNNNNOI+N~IOZ...... 7~..     \n");
    printf("    .,+. ........=Z7....:Z$$I....,........Z:..~$NN8N8NM8N8NO.N=8D......$=...     \n");
    printf("     .~I ...............$$$$$$77$........IO.......MNONO8N==O7N.D.......?,..      \n");
    printf("     .,+...............$$$$$7,..,.......,?~..+?O..,$OMDNDZ+8M88...... O~..       \n");
    printf("      ,~:............7$$I.,....:........7Z...::...D7$$ZDNMNN887......I?,..       \n");
    printf("     ..,?..........+,.. ...,...~.......,,+...~.:.ZZ7OZ+,.............$~. .       \n");
    printf("       .~?...............,.,...~..........:ONOM8$$$$Z,...=7,.....$..Z=.          \n");
    printf("        :?...............,.,...:?,...........?DN8ONN...OOI?:..O,?. .?,.          \n");
    printf("       .,~?................,....,=$O,............$O87..,88D8..~... Z~..          \n");
    printf("        .:+.. ........... .,......:~=ION................D:...M,...7?,..          \n");
    printf("        .,~~...............,....... ,7???IZO?...............=?N..,7: .           \n");
    printf("         .,+  ..................??+=~,,...,:=I$8,.,.........M.D..Z=,.            \n");
    printf("          .=+........... ..~I+=~:,....    ....,:+I$Z,, ....=.~..,?,              \n");
    printf("         . :+=........~I?=~:...... .        .  . .,~+?ZO,......=7:.              \n");
    printf("          ..:=II::?I==:,,.. ..                      ..,~+7$8ZDZ?~.               \n");
    printf("\n                Welcome to the famous David Nadeau Casino!                   \n\n");
}
void print_hand(int *hand, char *user)
{
    char card_rank, suite;
    int i, card_count;
    card_count = count_cards(hand);
    printf("%s: ", user);
    for (i = 0; i < card_count; ++i)
    {
        card_rank = get_rank(hand[i]);
        suite = get_suite(hand[i]);
        printf("%c%c\t",card_rank,suite);
    }
    printf("\n");
}

/*
---------------------------------------------------
 *  Methods dealing with game logic
----------------------------------------------------
*/
void initial_deal()
{
    house_hand[0]  = get_new_card();

    player_hand[0] = get_new_card();
    player_hand[1] = get_new_card();
}
void player_loop()
{
    int icard;//stores index where the store new cards will be placed in players hand
    int score;
    char card_rank, suite;
    while (1)
    {
        printf("h/s: ");
        getchar();
        if ( getchar() == 'h')
        {
            printf("IN H\n");
            icard = count_cards(player_hand);
            player_hand[icard] = get_new_card();
            card_rank = get_rank(player_hand[icard]);
            suite = get_suite(player_hand[icard]);
            printf("%c%c\n",card_rank,suite);
            score = tally_hand(player_hand);
            if (score > 21)
            {
                busted = 1;
                break;
            }
        }else
            break;
    }
}
void house_loop()
{
    int icard;//store amt of cards in house hand
    while (1)
    {
        //make method to prnit total of array
        if (tally_hand(house_hand) < 18)
        {
            icard = count_cards(house_hand);
            house_hand[icard] = get_new_card();
        }else
        {
            print_hand(house_hand,"Dealer");
            break;
        }
    }
}
void judgement()
{
    int house, player;
    house = tally_hand(house_hand);
    player = tally_hand(player_hand);

    house = 21-house;
    player = 21-player;

    if (house < 0)
        printf("Player: %d, Dealer: %d You Win!\n",tally_hand(player_hand),tally_hand(house_hand));
    else if (player < house)
        printf("Player: %d, Dealer: %d You Win!\n",tally_hand(player_hand),tally_hand(house_hand));
    else if (player > house)
        printf("Player: %d, Dealer: %d You Lose!\n",tally_hand(player_hand),tally_hand(house_hand));
    else if (player == house)
        printf("Player: %d, Dealer: %d Push, no winner!\n",tally_hand(player_hand),tally_hand(house_hand));
}

/*
---------------------------------------------------
 *  Main
----------------------------------------------------
*/
int main()
{
    show_welcome();
    load_deck();
    while (1)
    {
        printf("Want to play blackjack? (y/n): ");
        if (getchar() == 'y')
        {
            clear_hand(player_hand);
            clear_hand(house_hand);
            shuffle_deck();
            initial_deal();
            print_hand(house_hand,"Dealer");
            print_hand(player_hand,"Player");
            player_loop();//go to the player logic loop
            if (busted)
            {
                printf("Player: %d, Dealer: %d You Lose!\n",tally_hand(player_hand),tally_hand(house_hand));
                busted = 0;
            }
            else
            {
                house_loop();//go to house logic loop
                judgement();
            }
        } else
        {
            printf("Thanks for playing. \n");
            break;
        }
        getchar();
    }
    return 0;
}
