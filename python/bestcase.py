# Assuming we play optimally by what the solver explored, only rolling the best
# choice, what's the best case we can hope for? What sequence of events is that?

from solve import State


def find_best_case_scenario(state: State) -> int:
    high_score = state.turn_score

    if state.best_choice == 0:  # Bank
        return high_score

    for next_state in state.next_states[state.best_choice]:
        score = find_best_case_scenario(next_state)  # Recursive
        if score > high_score:
            high_score = score

    return high_score


def find_best_sequence(state: State, sequence = "") -> tuple[int, str]:
    high_score = state.turn_score
    best_sequence = sequence

    if state.best_choice == 0:  # Bank
        return high_score, best_sequence + " Bank"

    for next_state in state.next_states[state.best_choice]:
        next_sequence = f"{sequence} d{state.best_choice}:{next_state.prev_roll}"
        next_score, next_sequence = find_best_sequence(next_state, next_sequence)  # Recursive
        if next_score > high_score:
            high_score = next_score
            best_sequence = next_sequence

    # Hack: so that state.display() prints the best sequence
    state.evaluation = f"{state.evaluation:.2f} | {best_sequence} {high_score}" # type: ignore

    return high_score, best_sequence


if __name__ == "__main__":
    state = State()
    state.explore()
    find_best_sequence(state)
    state.display()
