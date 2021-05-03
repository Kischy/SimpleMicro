#include <gtest/gtest.h>

#include "../LList/LList.h"

#include "IListCommonTests.h"


INSTANTIATE_TEST_SUITE_P(LListTests,
                         LListBaseTests,
                         testing::Values(std::make_shared<smpmcr::LList<int>>()));



INSTANTIATE_TEST_SUITE_P(LListIteratorAndFrontTests,
                         LListBaseIteratorAndFrontTests,
                         testing::Values(std::make_shared<smpmcr::LList<int>>()));




INSTANTIATE_TEST_SUITE_P(LListIteratorArrowOperatorTests,
                         LListBaseIteratorArrowOperatorTests,
                         testing::Values(std::make_shared<smpmcr::LList<IntHolder>>()));





