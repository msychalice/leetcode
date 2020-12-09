#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

template<class Container>
void printContainer(const Container& container) {
//    return;

    if (container.size() == 0) {
        cout << "[]" << endl;
        return;
    }

    for (auto it = container.begin(); it != container.end(); it++) {
        if (it == container.begin()) {
            cout << "[";
        }
        cout << *it;
        if (it == prev(container.end())) {
            cout << "]" << endl;
        } else {
            cout << ", ";
        }
    }
}

template<class T>
void print2DimVec(const vector<vector<T>>& container) {
//    return;

    if (container.size() == 0) {
        cout << "[]" << endl;
        return;
    }

    for (auto it = container.begin(); it != container.end(); it++) {
        if (it == container.begin()) {
            cout << "[" << endl;
        }
        printContainer(*it);
        if (it == prev(container.end())) {
            cout << "]" << endl;
        }
    }
}

template<class T>
void printMap(const T& container) {
//    return;

    cout << "size " << container.size() << endl;
    if (container.size() == 0) {
        cout << "[]" << endl;
        return;
    }
    for (auto it = container.begin(); it != container.end(); it++) {
        if (it == container.begin()) {
            cout << "[ ";
        }

        cout << "[" << it->first << ", " << it->second << "]";

        if (next(it) == container.end()) {
            cout << " ]" << endl;
        } else {
            cout << ", ";
        }
    }
}

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

void printList(const ListNode* node) {
    while (node != nullptr) {
        cout << node->val;

        node = node->next;
        
        if (node != nullptr) {
            cout << "->";
        } else {
            cout << endl;
        }
    }
}

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

void printTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    cout << root->val << endl;
    printTree(root->left);
    printTree(root->right);
}

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;
    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Twitter {
    class User;
    class Tweet {
    public:
        explicit Tweet(int tweetId, User* pUser)
            : m_tweetId(tweetId),
              m_timestamp(Twitter::getTimeStamp()),
              m_pUser(pUser) {}

        int getTweetId() const {
            return m_tweetId;
        }
        int getTimeStamp() const {
            return m_timestamp;
        }
        User* getUser() const {
            return m_pUser;
        }

        // used in priority_queue
        bool operator<(const Tweet& rhs) const {
            return m_timestamp < rhs.m_timestamp;
        }

    private:
        int m_tweetId;
        int m_timestamp;
        User* m_pUser;
    };

    class User {
    public:
        explicit User(int userId) : m_userId(userId) {}

        void postTweet(int tweetId) {
            m_tweets.push_back(new Tweet(tweetId, this));
        }

        void follow(User* followee) {
            if (followee == nullptr) {
                return;
            }
            m_followees.insert(followee);
        }

        void unfollow(User* followee) {
            if (followee == nullptr) {
                return;
            }
            m_followees.erase(followee);
        }

        // position = 0 means get the most recent published tweet
        Tweet* getTweet(int position) const {
            if (position >= m_tweets.size()) {
                return nullptr;
            }
            return m_tweets[m_tweets.size() - 1 - position];
        }

        const unordered_set<User*>& getFollowees() const {
            return m_followees;
        }

    private:
        int m_userId;
        vector<Tweet*> m_tweets;
        unordered_set<User*> m_followees;
    };

public:
    /** Initialize your data structure here. */
    Twitter() {}

    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        getUser(userId)->postTweet(tweetId);
    }

    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item
     * in the news feed must be posted by users who the user followed or by the
     * user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        vector<int> output;
        priority_queue<Tweet> pqTweets;
        constexpr int MaxTweets = 10;

        unordered_map<User*, int> mapUserTweetPos;

        User* pUser = getUser(userId);
        Tweet* pTweet = pUser->getTweet(0);
        if (pTweet != nullptr) {
            pqTweets.push(*pTweet);
            mapUserTweetPos.emplace(pUser, 0);
        }

        for (const auto& followee : pUser->getFollowees()) {
            pTweet = followee->getTweet(0);
            if (pTweet != nullptr) {
                pqTweets.push(*pTweet);
                mapUserTweetPos.emplace(followee, 0);
            }
        }

        while (pqTweets.size() > 0) {
            output.push_back(pqTweets.top().getTweetId());

            if (output.size() == MaxTweets) {
                break;
            }

            pUser = pqTweets.top().getUser();
            pqTweets.pop();

            int curTweetPos = mapUserTweetPos[pUser] + 1;
            pTweet = pUser->getTweet(curTweetPos);
            if (pTweet != nullptr) {
                pqTweets.push(*pTweet);
                mapUserTweetPos[pUser] = curTweetPos;
            }
        }

        return output;
    }

    /** Follower follows a followee. If the operation is invalid, it should be a
     * no-op. */
    void follow(int followerId, int followeeId) {
        if (followerId == followeeId) {
            return;
        }
        getUser(followerId)->follow(getUser(followeeId));
    }

    /** Follower unfollows a followee. If the operation is invalid, it should be
     * a no-op. */
    void unfollow(int followerId, int followeeId) {
        if (followerId == followeeId) {
            return;
        }
        getUser(followerId)->unfollow(getUser(followeeId));
    }

private:
    User* getUser(int userId) {
        User* pUser;
        auto it = m_mapUsers.find(userId);
        if (it != m_mapUsers.end()) {
            pUser = it->second;
        } else {
            pUser = new User(userId);
            m_mapUsers.emplace(userId, pUser);
        }
        return pUser;
    }

    static int getTimeStamp() {
        static int s_timestamp = 0;
        return s_timestamp++;
    }

    unordered_map<int, User*> m_mapUsers;
};

int main() {
    Twitter* obj = new Twitter();
    obj->postTweet(1, 2);
    printContainer(obj->getNewsFeed(1));
    obj->follow(1, 2);
    obj->postTweet(2, 6);
    printContainer(obj->getNewsFeed(1));
    obj->unfollow(1, 2);
    printContainer(obj->getNewsFeed(1));

    cout << "*************output*************" << endl;

    return 0;
}
