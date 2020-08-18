#include <iostream>
#include <vector>
#include <math.h>
#include <bitset>

class Disc
{
public:
    int disc_size;

    Disc(int s) :disc_size(s)
    {}

    Disc(const Disc& copy)
        : disc_size(copy.disc_size)
    { }
};


int main()
{
    int size;

    std::cout << "Insert size: ";
    std::cin >> size;
    std::cout << std::endl;

    std::vector<Disc> towers[3];

#pragma region create game

    for (int i = size-1; i >= 0; i--)
    {
        towers[0].emplace_back(Disc(pow(2,i)));
    }

#pragma endregion

#pragma region draw
    for (std::vector<Disc> x : towers)
    {
        std::cout << "Tower: ";

        for (int i = 0; i < x.size(); i++)
        {
            std::cout << x[i].disc_size << " ";
        }

        std::cout << "\n";
    }
    std::cout << "\n";
#pragma endregion


    int helper = 1;

    while (helper <= pow(2, size) - 1)
    {
        int previous = helper - 1;
        previous = previous & helper;

        int index = previous ^ helper;

        /*
        std::cout << "p: " << std::bitset<4>(previous) << std::endl;
        std::cout << "h: " << std::bitset<4>(helper) << std::endl;
        std::cout << "i: " << std::bitset<4>(index) << std::endl << std::endl;
        */

        //std::cout << index << " ";

        bool moved = false;

        int towersSize = 3;
        //int towersSize = towers->size();

        for (int i = 0; i < towersSize; i++)
        {
             for (int j = 0; j < towers[i].size(); j++)
            {
                if (towers[i][j].disc_size == index)
                {
                    Disc selectedDisc = Disc(towers[i][j]);
                    int dstTower;
                    
                    if (size % 2)
                    {
                        if (i == 0)
                        {
                            if (towers[i + 2].empty() || towers[i + 2][towers[i + 2].size() - 1].disc_size > selectedDisc.disc_size)
                                dstTower = i + 2;
                            else
                                dstTower = i + 1;
                        }

                        else if (i == 1)
                        {
                            if (towers[i - 1].empty() || towers[i - 1][towers[i - 1].size() - 1].disc_size > selectedDisc.disc_size)
                                dstTower = i - 1;
                            else
                                dstTower = i + 1;
                        }

                        else if (i == 2)
                        {
                            if (towers[i - 1].empty() || towers[i - 1][towers[i - 1].size() - 1].disc_size > selectedDisc.disc_size)
                                dstTower = i - 1;
                            else
                                dstTower = i - 2;
                        }
                    }
                    else
                    {
                        if (i == 0)
                        {
                            if (towers[i + 1].empty() || towers[i + 1][towers[i + 1].size() - 1].disc_size > selectedDisc.disc_size)
                                dstTower = i + 1;
                            else
                                dstTower = i + 2;
                        }

                        else if (i == 1)
                        {
                            if (towers[i + 1].empty() || towers[i + 1][towers[i + 1].size() - 1].disc_size > selectedDisc.disc_size)
                                dstTower = i + 1;
                            else
                                dstTower = i - 1;
                        }

                        else if (i == 2)
                        {
                            if (towers[i - 2].empty() || towers[i - 2][towers[i - 2].size() - 1].disc_size > selectedDisc.disc_size)
                                dstTower = i - 2;
                            else
                                dstTower = i - 1;
                        }
                    }

                    towers[dstTower].push_back(selectedDisc);
                    towers[i].pop_back();

                    moved = true;

                    for (std::vector<Disc> x : towers)
                    {
                        std::cout << "Tower: ";

                        for (int i = 0; i < x.size(); i++)
                        {
                            std::cout << x[i].disc_size << " ";
                        }

                        std::cout << "\n";
                    }
                    std::cout << "\n";

                    break;
                    //std::cout << selectedDisc.disc_size << " ";
                }
            }

             if (moved)
             {
                 break;
             }
        }

        helper++;
    }
    system("pause");
}