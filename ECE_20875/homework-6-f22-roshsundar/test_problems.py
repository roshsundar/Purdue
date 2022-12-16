import unittest
import problems


class TestProblem1(unittest.TestCase):
    def test_simple(self):
        self.assertTrue(problems.problem1("byoda@jediacademy.edu"))

    def test_simple_with_numbers(self):
        self.assertTrue(problems.problem1("mwindu0123@jediacademy.edu"))

    def test_bad_suffix(self):
        self.assertFalse(
            problems.problem1("maul@jediacademy.eduasdf"), "Breaks rule #4."
        )

    def test_too_many_numbers(self):
        self.assertFalse(
            problems.problem1("vader99999@jediacademy.edu"), "Breaks rule #2."
        )

    def test_bad_domain(self):
        self.assertFalse(
            problems.problem1("byoda@notjediacademy.edu"), "Breaks rule #3."
        )

    def test_too_many_letters(self):
        self.assertFalse(
            problems.problem1("darthsidious@jediacademy.edu"), "Breaks rule #2."
        )

    def test_numbers_mixed(self):
        self.assertFalse(
            problems.problem1("r2d2@jediacademy.edu"), "Numbers between letters."
        )

    def test_fewer_than_4_digits(self):
        self.assertTrue(problems.problem1("vader999@jediacademy.edu"))

    def test_leading_zeros_accepted(self):
        self.assertTrue(
            problems.problem1("vader0999@jediacademy.edu"),
            "We accept leading zeros, but not when there are more than 4 digits.",
        )

    def test_too_many_zeros(self):
        self.assertFalse(
            problems.problem1("vader00999@jediacademy.edu"), "Breaks rule #2."
        )

    def test_starts_with_numbers(self):
        self.assertFalse(problems.problem1("7658@jediacademy.edu"), "Breaks rule #1.")

    def test_escaped_period(self):
        self.assertFalse(
            problems.problem1("byoda@jediacademyoedu"),
            'Breaks rule #3, did you forget to escape your "."?.',
        )

    def test_space_at_front(self):
        self.assertFalse(
            problems.problem1(" byoda@jediacademy.edu"),
            "We don't accept leading spaces.",
        )

    def test_space_at_end(self):
        self.assertFalse(
            problems.problem1("byoda@jediacademy.edu "),
            "We don't accept trailing spaces.",
        )


class TestProblem2(unittest.TestCase):
    def test_simple(self):
        self.assertTupleEqual(
            problems.problem2("Luke Skywalker flies the X-wing"),
            ("Luke Skywalker", "X-wing"),
        )

    def test_more_words(self):
        self.assertTupleEqual(
            problems.problem2(
                "It is quite impressive to see how well Hera flies the B-wing around the rocks"
            ),
            ("Hera", "B-wing"),
        )

    def test_flies_the(self):
        self.assertTupleEqual(
            problems.problem2(
                "Undeniabliy Chewbacca flies the most in his family, but Han Solo flies the YT-1300 even more."
            ),
            ("Han Solo", "YT-1300"),
        )

    def test_bad_name(self):
        self.assertTupleEqual(
            problems.problem2(
                "No one flies the X-wing like Luke, though Rey flies the YT-1300 very very well"
            ),
            ("Rey", "YT-1300"),
        )

    def test_bad_ship(self):
        self.assertTupleEqual(
            problems.problem2("Vader files the TIE fighter with high precision."),
            ("noname", "noship"),
        )

    def test_lowercase_ship(self):
        self.assertTupleEqual(
            problems.problem2("Luke Skywalker flies the x-wing"),
            ("noname", "noship"),
        )


class TestProblem3(unittest.TestCase):
    def test_simple_jedi(self):
        self.assertEqual(
            problems.problem3("Hello Jedi apprentice Yoda!"),
            "Hello Jedi Master Yoda!",
        )

    def test_lowercase_jedi(self):
        self.assertEqual(
            problems.problem3("Hello jedi Apprentice Yoda!"),
            "Hello jedi Master Yoda!",
        )

    def test_simple_sith(self):
        self.assertEqual(
            problems.problem3("Run!!!!! Sith Apprentice Sidious approaches!"),
            "Run!!!!! Sith Darth Sidious approaches!",
        )

    def test_lowercase_sith(self):
        self.assertEqual(
            problems.problem3("Run!!!!! sith apprentice Sidious approaches!"),
            "Run!!!!! sith Darth Sidious approaches!",
        )

    def test_extra_apprentice(self):
        self.assertEqual(
            problems.problem3(
                "Baby Yoda is your apprentice now, teach him to be a Jedi, Jedi apprentice Luke!"
            ),
            "Baby Yoda is your apprentice now, teach him to be a Jedi, Jedi Master Luke!",
        )

    def test_extra_apprentice_with_sith(self):
        self.assertEqual(
            problems.problem3(
                "Although Maul was an apprentice to sith apprentice Sidious, he is not half the sith lord he wanted to be."
            ),
            "Although Maul was an apprentice to sith Darth Sidious, he is not half the sith lord he wanted to be.",
        )

    def test_no_match(self):
        self.assertEqual(problems.problem3("Hello Jedi Knight Kenobi"), "nomatch")


if __name__ == "__main__":
    print("Reminder, these test cases are NOT exhaustive.")
    print("Passing these cases does not guarantee you will get full credit.")
    unittest.main()
