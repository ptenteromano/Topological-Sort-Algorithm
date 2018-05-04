# Topological-Sort-Algorithm
Given a Directed Acyclic Graph (DAG), return a Topological sort of it's Vertices


Data files are input with DAG information.

The algorithm returns a Topological Sort (There can be more than one valid answer)

The method I use:
  1. Map Indegrees (hash map of 'V' -> inbound edges)
  2. Pop sources (a source has 0 inbound edges)
  3. Remove source node and it's Outbound edges
    - This will create more Sources, or |V| = 0
  4. Repeat until |V| = 0
