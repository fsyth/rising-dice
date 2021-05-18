#include "displaySolverResults.hpp"

#include "solve.hpp"

#include <iostream>

void indent(const TurnNode& turn)
{
	for (int i = 0; i < turn.state.rollNo; ++i) std::cout << "    ";
}

void displayTurnNode(const TurnNode& turn)
{
	if (turn.bestChoiceNext == Bank) return;

	indent(turn);
	std::cout << turn.state.prevRoll << ": "
	          << turn.bestChoiceNext << " (" << turn.expectedScore << ")\n";

	for (const auto& [roll, nextTurnNode] : turn.next.at(turn.bestChoiceNext))
		displayTurnNode(nextTurnNode);
}

void displaySolverResults()
{
	const TurnNode& root = solve();

	displayTurnNode(root);
}

void displayTurnNodeHtml(const TurnNode& turn)
{
	if (turn.bestChoiceNext == Bank) return;

	indent(turn);
	std::cout << "<div class='tree'><button class='tree-button'>"
	          << turn.state.prevRoll << ": "
	          << turn.bestChoiceNext << " (" << turn.expectedScore << ")</button>"
	          << "<div class='collapsed'>" << "\n";

	for (const auto& [roll, nextTurnNode] : turn.next.at(turn.bestChoiceNext))
		displayTurnNodeHtml(nextTurnNode);

	indent(turn);
	std::cout << "</div></div>\n";
}

void displaySolverResultsHtml()
{
	const TurnNode& root = solve();

	std::cout << R"(
<html>
  <style>
    .collapsed { display: none; }
    .tree { margin-left: 40px; }
  </style>
  <script>
    function toggleCollapsed(e) {
      e.target.nextSibling.classList.toggle('collapsed')
    }

    document.addEventListener('DOMContentLoaded', () => {
      const buttons = document.getElementsByClassName('tree-button')
      for (let b of buttons) b.addEventListener('click', toggleCollapsed)
    })
  </script>
  <body>
)";
	displayTurnNodeHtml(root);
	std::cout << "  </body>\n</html>\n";
}

void displayTurnNodeJson(const TurnNode& turn)
{
	if (turn.bestChoiceNext == Bank) return;

	indent(turn);
	std::cout << '"' << turn.state.prevRoll << "\": {"
	          << '"' << turn.bestChoiceNext << "\": {\n";

	for (const auto& [roll, nextTurnNode] : turn.next.at(turn.bestChoiceNext))
		displayTurnNodeJson(nextTurnNode);

	indent(turn);
	std::cout << "}},\n";
}

void displaySolverResultsJson()
{
	const TurnNode& root = solve();

	std::cout << '{';
	displayTurnNodeJson(root);
	std::cout << '}';
}
