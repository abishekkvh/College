import java.util.*;

public class BurRoutes {
    public int numBusesToDestination(int[][] routes, int source, int target) {
        // If you are already at the destination, 0 buses are needed.
        if (source == target) {
            return 0;
        }

        int n = routes.length;

        // Map each stop to all the bus routes that pass through it.
        Map<Integer, List<Integer>> stopToRoutes = new HashMap<>();
        for (int i = 0; i < n; i++) {
            for (int stop : routes[i]) {
                stopToRoutes.computeIfAbsent(stop, k -> new ArrayList<>()).add(i);
            }
        }

        // If source or target doesn't exist in any route, a path is impossible.
        if (!stopToRoutes.containsKey(source) || !stopToRoutes.containsKey(target)) {
            return -1;
        }

        // BFS setup: queue stores the current stop.
        Queue<Integer> queue = new LinkedList<>();
        // Set to track visited stops to avoid redundant processing.
        Set<Integer> visitedStops = new HashSet<>();
        // Array to track visited bus routes to avoid re-boarding the same bus.
        boolean[] visitedRoutes = new boolean[n];

        queue.offer(source);
        visitedStops.add(source);
        int busCount = 0;

        // Standard level-by-level BFS execution
        while (!queue.isEmpty()) {
            int size = queue.size();
            busCount++;

            // Process all stops at the current "transfer level"
            for (int i = 0; i < size; i++) {
                int currentStop = queue.poll();

                // Get all bus routes passing through the current stop
                for (int routeId : stopToRoutes.get(currentStop)) {
                    if (visitedRoutes[routeId]) {
                        continue;
                    }
                    visitedRoutes[routeId] = true;

                    // Explore all stops reachable via this bus route
                    for (int nextStop : routes[routeId]) {
                        if (nextStop == target) {
                            return busCount;
                        }
                        if (!visitedStops.contains(nextStop)) {
                            visitedStops.add(nextStop);
                            queue.offer(nextStop);
                        }
                    }
                }
            }
        }

        return -1;
    }

    public static void main(String[] args) {
        BurRoutes obj = new BurRoutes();
        int[][] routes = {{1,2,7},{3,6,7}};
        int source = 1, target = 6;
        System.out.println("Num Buses: " + obj.numBusesToDestination(routes, source, target));
    }
}
