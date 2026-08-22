# In the endgame, we no longer care about maximising our average score per turn.
# We only care about crossing the finish line.
# The maximum score in a turn is 60 points, so we are in the endgame if we are 
# at most 60 points away from the finish line.
# However, playing a turn optimally will never attempt to score 60 in a single
# turn since it is too unlikely to go for, so there is a lower practical endgame
# limit, which we can base on the maximum score that `solve` found, which is 41.
# Ideally, we finish in a single turn, but there is a probability of failing,
# in which case we might be able to finish from a closer position next turn.
# For every distance to the finish line, there is a probability distribution for
# the number of turns it will take to finish, and therefore a fractional 
# expected number of turns to finish.
# With that, we can make choices that minimise the expected turns to finish.
# However, if we constantly go bust, we will never get to the finish. We need
# to take the limit in this case, based on the bust probability.

from functools import cache

from solve import State


state = State()
state.explore()


@cache
def expectedTurns(distance: int):
    if distance < 1:
        return 0

    # return (1 + sum(p_x * expectedTurns(distance - x) for x in range(distance + 1)) / (1 - p_bust)
    pass
