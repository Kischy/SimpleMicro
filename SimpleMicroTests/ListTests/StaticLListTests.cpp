#include "LListBaseCommonTests.h"
#include "../../LList/StaticLList.h"


INSTANTIATE_TEST_SUITE_P(StaticLListTests,
                         LListBaseTests,
                         testing::Values(std::make_shared<smpmcr::StaticLList<int,100>>()));



INSTANTIATE_TEST_SUITE_P(StaticLListEraseTests,
                         LListBaseEraseTests,
                         testing::Values(std::make_shared<smpmcr::StaticLList<long,100>>()));


INSTANTIATE_TEST_SUITE_P(StaticLListIteratorAndFrontTests,
                         LListBaseIteratorAndFrontTests,
                         testing::Values(std::make_shared<smpmcr::StaticLList<int,100>>()));



INSTANTIATE_TEST_SUITE_P(StaticLListIteratorArrowOperatorTests,
                         LListBaseIteratorArrowOperatorTests,
                         testing::Values(std::make_shared<smpmcr::StaticLList<IntHolder,100>>()));

                         




TEST(StaticLListMaxSizeTests,MaxSizeReturnsCorrectValue)
{    

    size_t size100 = smpmcr::StaticLList<long,100>::max_size();
    ASSERT_EQ(size100,100);
    
    size_t size4 = smpmcr::StaticLList<char,4>::max_size();
    ASSERT_EQ(size4,4);    

    smpmcr::StaticLList<char,6> testList;
    ASSERT_EQ(testList.max_size(),6);
}





