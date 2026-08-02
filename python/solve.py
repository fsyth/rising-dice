# This is a dice game I invented, and a solver to explore the optimal strategy.
#
# The rules of the game are simple:
# On your turn, you start with a d4, d6, d8, d10, and d12 available to roll.
# Each roll gets added to your potential score for this turn.
# After you roll a die, you can either bank your score, or roll again.
# If you roll again, it must be a die you haven't rolled yet this turn.
# However, if you rolled less than your previous roll this turn, you go bust
# and bank nothing for the turn.
# Also, if you roll all five dice without going bust, a d20 becomes available.

class State:
    def __init__(self):
        # Game state
        self.choices = { 4, 6, 8, 10, 12 }
        self.prev_roll = 0
        self.roll_count = 0
        self.turn_score = 0

        # Solver evaluation
        self.next_states = dict[int, list[State]]()  # [die][roll-1]
        self.best_choice = 0
        self.evaluation = 0


    def roll_next_state(self, die: int, roll: int) -> 'State':
        if die not in self.choices:
            raise ValueError(f"d{die} is not available to roll.")

        if roll < 1 or roll > die:
            raise ValueError(f"d{die} cannot possibly roll {roll}.")

        next = State()
        next.prev_roll = roll
        next.roll_count = self.roll_count + 1

        if roll < self.prev_roll:
            # Bust
            next.turn_score = 0
            next.choices.clear()
            return next

        # Safe
        next.turn_score = self.turn_score + roll
        next.choices = {d for d in self.choices if d >= roll}
        next.choices.remove(die)
        if next.roll_count == 5:
            next.choices.add(20)

        return next


    def explore(self):
        self.best_choice = 0  # Bank
        self.evaluation = self.turn_score

        for die in self.choices:
            die_states = list[State]()
            self.next_states[die] = die_states

            for roll in range(1, die + 1):
                next = self.roll_next_state(die, roll)
                next.explore()  # Recursive
                die_states.append(next)

            die_evaluation = sum(s.evaluation for s in die_states) / len(die_states)

            if die_evaluation > self.evaluation:
                self.best_choice = die
                self.evaluation = die_evaluation


    def display(self):
        if self.best_choice == 0:  # Bank
            return  # No further display

        indent = "    " * self.roll_count
        print(f"{indent}{self.prev_roll}: d{self.best_choice} ({self.evaluation})")
        for next in self.next_states[self.best_choice]:
            next.display()


if __name__ == "__main__":
    state = State()
    state.explore()
    state.display()
