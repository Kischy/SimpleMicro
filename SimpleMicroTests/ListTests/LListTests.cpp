#include "LListBaseCommonTests.h"
#include "../../LList/LList.h"


INSTANTIATE_TEST_SUITE_P(LListTests,
                         LListBaseTests,
                         testing::Values(std::make_shared<smpmcr::LList<int>>()));



INSTANTIATE_TEST_SUITE_P(LListEraseTests,
                         LListBaseEraseTests,
                         testing::Values(std::make_shared<smpmcr::LList<long>>()));


INSTANTIATE_TEST_SUITE_P(LListIteratorAndFrontTests,
                         LListBaseIteratorAndFrontTests,
                         testing::Values(std::make_shared<smpmcr::LList<int>>()));



INSTANTIATE_TEST_SUITE_P(LListIteratorArrowOperatorTests,
                         LListBaseIteratorArrowOperatorTests,
                         testing::Values(std::make_shared<smpmcr::LList<IntHolder>>()));





