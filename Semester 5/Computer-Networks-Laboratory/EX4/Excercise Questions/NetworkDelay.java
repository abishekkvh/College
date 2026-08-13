import java.util.*;

public class NetworkDelay {
    public int networkDelayTime(int[][] times, int n, int k) {
        // Build the adjacency list graph: node -> List of [neighbor, time]
        Map<Integer, List<int[]>> graph = new HashMap<>();
        for (int[] edge : times) {
            graph.computeIfAbsent(edge[0], x -> new ArrayList<>()).add(new int[] { edge[1], edge[2] });
        }

        // Min-heap to store [cumulative_time, node] sorted by cumulative_time
        PriorityQueue<int[]> minHeap = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));
        minHeap.offer(new int[] { 0, k });

        // Map to store the minimum time to reach each node
        Map<Integer, Integer> visitedDistances = new HashMap<>();

        while (!minHeap.isEmpty()) {
            int[] current = minHeap.poll();
            int signalTime = current[0];
            int currentNode = current[1];

            // If we have already found a shorter path to this node, skip it
            if (visitedDistances.containsKey(currentNode)) {
                continue;
            }
            visitedDistances.put(currentNode, signalTime);

            // Explore all outbound connections
            if (graph.containsKey(currentNode)) {
                for (int[] neighborInfo : graph.get(currentNode)) {
                    int neighbor = neighborInfo[0];
                    int travelTime = neighborInfo[1];

                    if (!visitedDistances.containsKey(neighbor)) {
                        minHeap.offer(new int[] { signalTime + travelTime, neighbor });
                    }
                }
            }
        }

        // If we haven't visited all n nodes, it's impossible for all to receive the
        // signal
        if (visitedDistances.size() != n) {
            return -1;
        }

        // The total time taken is the maximum time required to reach any node
        int maxDelay = 0;
        for (int time : visitedDistances.values()) {
            maxDelay = Math.max(maxDelay, time);
        }

        return maxDelay;
    }

    public static void main(String[] args) {
        NetworkDelay obj = new NetworkDelay();
        int[][] times = {{2,1,1},{2,3,1},{3,4,1}};
        int n = 4, k = 2;
        System.out.println("Network Delay Time: " + obj.networkDelayTime(times, n, k));
    }
}
