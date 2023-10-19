// Unit Test - Simple Unit Test using GoogleTest framework
// Author: Alexander Cardoso

#include <iostream>
#include <exception>

// Unit Test framework from Google - GoogleTest
#include <gtest/gtest.h>

// Only absolute value - Not exists negative age
typedef unsigned int uint;


namespace department
{
    // Generic "vote department" class 
    class VoteDepartment
    {
        public:
        VoteDepartment() {}

        private:
        bool m_isFit;

        public:
        uint getStatus() const { return m_isFit; }
        void setStatusByAge(uint age, bool isInPrison, bool isDeficient);
    };
}


void department::VoteDepartment::setStatusByAge(uint age, bool isInPrison, bool isDeficient)
{
    try {
        if (!isInPrison && !isDeficient) {
            if (age >= 16 && age < 18) {
                // Can vote - Not obligatory
                m_isFit = false;
            } if (age >= 18 && age < 70) {
                // Can vote - Obligatory
                m_isFit = true;
            } else if (age >= 70) {
                // Can vote - Not obligatory
                m_isFit = false;
            }
        } else {
            std::cout << "\n[*] Prisoned or deficient people cannot vote.\n";
            m_isFit = false;
            return;
        }
    } catch (std::exception &e) {
        std::cerr << "[ERROR]: " << e.what() << "\n";
        throw;
        return;
    }
}


class DepartmentUnitTest : public ::testing::Test
{
    /*
        IN BACKLOG
    */
    protected:
    void SetUp() override
    { }
    void TearDown() override
    { }
};


// Test 1 - Not obligatory - Exp: False
TEST_F(DepartmentUnitTest, NotObligatory)
{
    department::VoteDepartment voteDepartment;

    voteDepartment.setStatusByAge(17, false, false);
    EXPECT_FALSE(voteDepartment.getStatus());
}


// Test 2 - Obligatory - Is in prison - Exp: False
TEST_F(DepartmentUnitTest, ObligatoryIsInPrison)
{
    department::VoteDepartment voteDepartment;

    voteDepartment.setStatusByAge(18, true, false);
    EXPECT_FALSE(voteDepartment.getStatus());
}


// Test 3 - Obligatory - Is deficient - Exp: False
TEST_F(DepartmentUnitTest, ObligatoryIsDeficient)
{
    department::VoteDepartment voteDepartment;

    voteDepartment.setStatusByAge(18, false, true);
    EXPECT_FALSE(voteDepartment.getStatus());
}


// Test 3 - Obligatory - Exp: True - 18 years
TEST_F(DepartmentUnitTest, Obligatory1)
{
    department::VoteDepartment voteDepartment;

    voteDepartment.setStatusByAge(18, false, false);
    EXPECT_TRUE(voteDepartment.getStatus());
}


// Test 4 - Obligatory - Exp: True - 69 years
TEST_F(DepartmentUnitTest, Obligatory2)
{
    department::VoteDepartment voteDepartment;

    voteDepartment.setStatusByAge(69, false, false);
    EXPECT_TRUE(voteDepartment.getStatus());
}


// Test 5 - Not Obligatory - Is old - Exp: False
TEST_F(DepartmentUnitTest, NotObligatory2)
{
    department::VoteDepartment voteDepartment;

    voteDepartment.setStatusByAge(70, false, true);
    EXPECT_FALSE(voteDepartment.getStatus());
}


// Test 6 - Testing error - force error:
TEST_F(DepartmentUnitTest, TestingTheError)
{
    department::VoteDepartment voteDepartment;

    voteDepartment.setStatusByAge(70, false, true);
    EXPECT_TRUE(voteDepartment.getStatus());
}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
