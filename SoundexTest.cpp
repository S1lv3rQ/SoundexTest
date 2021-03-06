#include "Soundex.h"
#include "gmock/gmock.h"
using ::testing::Eq;
// Create a class fixture
class SoundexEncoding : public testing::Test
{
public:
    Soundex soundex;
};

TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord)
{
    //Arrange
    //Act //Assert
    ASSERT_THAT(soundex.encode("A"), testing::Eq("A000"));
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits)
{
    //Arrange
    //Act //Assert
    ASSERT_THAT(soundex.encode("I"), testing::Eq("I000"));
}

TEST_F(SoundexEncoding, ReplaceConsonantsWithAppropriateDigits)
{
    //Arrange
    //Act //Assert
    // Note: Expect does not fail the test, assert does
    // Best practice states to only use EXPECT when
    // developing the code, not in production
    ASSERT_THAT(soundex.encode("Ab"), Eq("A100"));
    ASSERT_THAT(soundex.encode("Ac"), Eq("A200"));
    ASSERT_THAT(soundex.encode("Ad"), Eq("A300"));
    ASSERT_THAT(soundex.encode("Ax"), Eq("A200"));
    EXPECT_THAT(soundex.encode("Alx"), Eq("A420"));
}

TEST_F(SoundexEncoding, IgnoreNonAlphabetics)
{
    // Arrange @ class fixture
    // Act & Assert
    ASSERT_THAT(soundex.encode("A#"), Eq("A000"));
}

TEST_F(SoundexEncoding, ReplaceMultipleConsonantsWithDigits)
{
    // Arrange @ class fixture
    // Act & Assert
    ASSERT_THAT(soundex.encode("Acdl"), Eq("A234"));
}

TEST_F(SoundexEncoding, LimitLengthToFourCharacters)
{
    // Arrange @ class fixture
    // Act & Assert
    ASSERT_THAT(soundex.encode("Dcdlb").length(), Eq(4u));
}

TEST_F(SoundexEncoding, CombineDuplicateEncodings)
{
    // Arrange @ class fixture
    // Act & Assert
    ASSERT_THAT(soundex.encodeDigit('b'), Eq(soundex.encodeDigit('f')));
    ASSERT_THAT(soundex.encodeDigit('x'), Eq(soundex.encodeDigit('g')));
    ASSERT_THAT(soundex.encodeDigit('d'), Eq(soundex.encodeDigit('t')));
    ASSERT_THAT(soundex.encode("Abfxgdt"), Eq("A123"));
    cout << soundex.encode("Abfxgdt");
}