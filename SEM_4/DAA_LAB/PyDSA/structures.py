"""
Quick syntax reference for common Python data structures.
"""

from collections import Counter, deque
import heapq


def list_examples():
	nums = [3, 1, 4]
	nums.append(1)
	nums.extend([5, 9])
	nums.sort()  # in-place ascending
	popped = nums.pop()  # removes last
	sliced = nums[1:3]  # sublist copy
	return nums, popped, sliced


def dict_examples():
	counts = {"a": 2, "b": 1}
	counts["c"] = counts.get("c", 0) + 1  # safe increment
	present = "a" in counts
	keys = list(counts.keys())
	vals = list(counts.values())
	items = list(counts.items())
	return counts, present, keys, vals, items


def set_examples():
	a = {1, 2, 3}
	b = {3, 4}
	union = a | b
	inter = a & b
	diff = a - b
	a.add(5)
	has_two = 2 in a
	return union, inter, diff, has_two


def tuple_examples():
	point = (2, 3)
	x, y = point  # tuple unpack
	return point, x, y


def stack_example():
	stack = []
	stack.append(1)
	stack.append(2)
	top = stack.pop()
	return stack, top


def queue_example():
	q = deque()
	q.append("first")
	q.append("second")
	front = q.popleft()
	return list(q), front


def priority_queue_example():
	data = [5, 1, 3]
	heapq.heapify(data)  # min-heap
	heapq.heappush(data, 2)
	smallest = heapq.heappop(data)
	return data, smallest


def counter_example():
	text = "banana"
	freq = Counter(text)
	most_common = freq.most_common(2)
	return freq, most_common


def main():
	print("Lists:", list_examples())
	print("Dicts:", dict_examples())
	print("Sets:", set_examples())
	print("Tuples:", tuple_examples())
	print("Stack:", stack_example())
	print("Queue:", queue_example())
	print("Priority queue:", priority_queue_example())
	print("Counter:", counter_example())


if __name__ == "__main__":
	main()
