from collections import defaultdict, deque
from typing import Deque, Dict, Hashable, Iterable, List, Set


class Graph:
	"""Unweighted graph with basic traversal helpers."""

	def __init__(self, directed: bool = False) -> None:
		self.directed = directed
		self._adj: Dict[Hashable, Set[Hashable]] = defaultdict(set)

	def add_node(self, node: Hashable) -> None:
		self._adj[node]  # touch to ensure presence

	def add_edge(self, src: Hashable, dst: Hashable) -> None:
		self._adj[src].add(dst)
		if not self.directed:
			self._adj[dst].add(src)
		else:
			self._adj[dst]  # keep dst visible even if no outgoing edges

	def neighbors(self, node: Hashable) -> Iterable[Hashable]:
		return self._adj.get(node, set())

	def bfs(self, start: Hashable) -> List[Hashable]:
		if start not in self._adj:
			return []
		visited: Set[Hashable] = {start}
		order: List[Hashable] = []
		queue: Deque[Hashable] = deque([start])
		while queue:
			node = queue.popleft()
			order.append(node)
			for nbr in self._adj[node]:
				if nbr not in visited:
					visited.add(nbr)
					queue.append(nbr)
		return order

	def dfs(self, start: Hashable) -> List[Hashable]:
		if start not in self._adj:
			return []
		visited: Set[Hashable] = set()
		order: List[Hashable] = []
		stack: List[Hashable] = [start]
		while stack:
			node = stack.pop()
			if node in visited:
				continue
			visited.add(node)
			order.append(node)
			# Push neighbors in reverse so earlier neighbors are visited first.
			for nbr in reversed(list(self._adj[node])):
				if nbr not in visited:
					stack.append(nbr)
		return order

	def level_order(self, start: Hashable) -> List[List[Hashable]]:
		"""Return nodes grouped by BFS level starting at the given node."""
		if start not in self._adj:
			return []
		levels: List[List[Hashable]] = []
		visited: Set[Hashable] = {start}
		queue: Deque[tuple[Hashable, int]] = deque([(start, 0)])
		while queue:
			node, depth = queue.popleft()
			if depth == len(levels):
				levels.append([])
			levels[depth].append(node)
			for nbr in self._adj[node]:
				if nbr not in visited:
					visited.add(nbr)
					queue.append((nbr, depth + 1))
		return levels

	def shortest_unweighted(self, start: Hashable) -> Dict[Hashable, int]:
		"""Unweighted shortest-path distances from start using BFS."""
		if start not in self._adj:
			return {}
		dist: Dict[Hashable, int] = {start: 0}
		queue: Deque[Hashable] = deque([start])
		while queue:
			node = queue.popleft()
			for nbr in self._adj[node]:
				if nbr not in dist:
					dist[nbr] = dist[node] + 1
					queue.append(nbr)
		return dist

	def __len__(self) -> int:  # number of nodes
		return len(self._adj)

	def __iter__(self):
		return iter(self._adj)

	def __contains__(self, node: object) -> bool:
		return node in self._adj

