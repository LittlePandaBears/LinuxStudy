#include "sort.h"

int main(void)
{
    SORT s;
    cout << endl;
    bool flag = true;
    // for (int choice = 1; choice < 7; choice++)
    // {
    //     cout<<"**" << choice << endl << endl;
    //     for (int i = 0; i < 5; i++)
    //     {
    //         s.showList();
    //         s.sort(choice);
    //         s.sort(SORT::HS);
    //         flag = s.check();
    //         if (flag == false)
    //         {
    //             cout << "false" << endl;
    //             s.showList();
    //         }
    //         s.showList();
    //         s.randList();
    //     }
    // }
    s.showList();
    s.sort(SORT::HS);
    s.showList();
    return 0;
}