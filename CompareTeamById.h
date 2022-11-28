//
// Created by idota on 28/11/2022.
//

#ifndef WET1_COMPARETEAMBYID_H
#define WET1_COMPARETEAMBYID_H


#include <memory>
class Team;

class CompareTeamById
{
    bool isLeftSmaller(std::shared_ptr<Team>& team, int currentId, bool mode);
    bool isLeftSmaller(std::shared_ptr<Team>& team, std::shared_ptr<Team>& currentTeam, bool mode);
    bool isEqual(std::shared_ptr<Team>& team, int currentId);
    bool isEqual(std::shared_ptr<Team>& team, std::shared_ptr<Team>& currentTeam);
};


#endif //WET1_COMPARETEAMBYID_H
