# This is a dice game I invented playable in the terminal.
#
# The rules of the game are simple:
# On your turn, you start with a d4, d6, d8, d10, and d12 available to roll.
# Each roll gets added to your potential score for this turn.
# After you roll a die, you can either bank your score, or roll again.
# If you roll again, it must be a die you haven't rolled yet this turn.
# However, if you rolled less than your previous roll this turn, you go bust
# and bank nothing for the turn.
# Also, if you roll all five dice without going bust, a d20 becomes available.
#
# First player to reach 100 points wins.

from random import randint


WINNING_SCORE = 100


class Game:
    def __init__(self):
        self.begin_game()


    def begin_game(self):
        self.game_score = 0
        self.turn_count = 0
        self.begin_turn()


    def begin_turn(self):
        self.choices = { 4, 6, 8, 10, 12 }
        self.prev_roll = 0
        self.roll_count = 0
        self.turn_score = 0


    def ask_choice(self):
        print(f"\nTurn score: {self.turn_score}")
        print(f"Prev roll:  {self.prev_roll}")
        dice_choices = "  ".join(f"d{die} ({die})" for die in sorted(self.choices))
        bank_choice = "Bank (0) " if self.turn_score > 0 else ""
        print(f"Choices:    {dice_choices} {bank_choice}")

        while True:
            try:
                chosen = int(input("> "))
                assert chosen == 0 or chosen in self.choices
                return chosen
            except:
                print("Invalid input.")


    def play_roll(self, die: int):
        if die not in self.choices:
            raise ValueError(f"d{die} is not available to roll.")

        roll = randint(1, die)
        is_bust = roll < self.prev_roll

        self.prev_roll = roll
        self.roll_count += 1

        if is_bust:
            self.turn_score = 0
            self.choices.clear()
            return

        self.turn_score += roll
        self.choices = {d for d in self.choices if d >= roll}
        self.choices.remove(die)
        if self.roll_count == 5:
            self.choices.add(20)


    def end_turn(self):
        self.game_score += self.turn_score
        self.turn_count += 1
        self.turn_score = 0


    def play_turn(self):
        self.begin_turn()
        print(f"\n== Turn {self.turn_count + 1} ==")

        while len(self.choices) > 0 or self.turn_score > 0:
            chosen = self.ask_choice()

            if chosen == 0:
                break
            else:
                self.play_roll(chosen)
                print(f"\nRolled {self.prev_roll}")

        print("\nBanked." if self.turn_score > 0 else "Bust!")
        self.end_turn()
        print(f"\nGame score: {self.game_score}")


    def play_game(self):
        while self.game_score < WINNING_SCORE:
            self.play_turn()

        print(f"\nVictory in {self.turn_count} turns!")


    def ask_play_again(self):
        print("\nPlay again?  Yes (y)  No (n)")

        while True:
            try:
                yes_or_no = input("> ").lower()
                assert yes_or_no in "yn"
                return yes_or_no == "y"
            except:
                print("Invalid input.")


    def play(self):
        while True:
            self.play_game()
            play_again = self.ask_play_again()

            if not play_again:
                break

            self.begin_game()


if __name__ == "__main__":
    state = Game()
    state.play()
