import java.util.*;

public class MinReorder {
    public int minReorder(int n, int[][] connections) {
        // Build an adjacency list where we track the neighbor and the original
        // direction.
        // We use a custom Pair class or an integer array: [neighbor,
        // isOriginalDirection]
        // isOriginalDirection = 1 means the edge goes from current city to neighbor.
        // isOriginalDirection = 0 means the edge goes from neighbor to current city.
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }

        for (int[] conn : connections) {
            int u = conn[0];
            int v = conn[1];
            // Original edge: u -> v (reordering needed if we move u -> v away from 0)
            graph.get(u).add(new int[] { v, 1 });
            // Reverse edge: v -> u (no reordering needed if we move v -> u toward 0)
            graph.get(v).add(new int[] { u, 0 });
        }

        // BFS Setup
        Queue<Integer> queue = new LinkedList<>();
        boolean[] visited = new boolean[n];

        queue.offer(0);
        visited[0] = true;
        int changeCount = 0;

        while (!queue.isEmpty()) {
            int current = queue.poll();

            for (int[] neighborInfo : graph.get(current)) {
                int neighbor = neighborInfo[0];
                int isOriginalDirection = neighborInfo[1];

                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    // If the original road points away from the capital (current -> neighbor),
                    // we must flip it to point toward the capital (neighbor -> current).
                    if (isOriginalDirection == 1) {
                        changeCount++;
                    }
                    queue.offer(neighbor);
                }
            }
        }

        return changeCount;
    }

    public static void main(String[] args) {
        MinReorder obj = new MinReorder();
        int n = 6;
        int[][] connections = {{0,1},{1,3},{2,3},{4,0},{4,5}};
        System.out.println("Min Reorder: " + obj.minReorder(n, connections));
    }
}
