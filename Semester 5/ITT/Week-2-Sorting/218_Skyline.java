import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.TreeMap;

class Skyline
{
    static class BuildingPoint implements Comparable<BuildingPoint> 
    {
        int x;
        boolean isStart;
        int height;

        @Override
        public int compareTo(BuildingPoint o) 
        {
            if (this.x != o.x) 
            {
                return this.x - o.x;
            } 
            else 
            {
                return (this.isStart ? -this.height : this.height) - (o.isStart ? -o.height : o.height);
            }
        }
    }

    public List<int[]> getSkyline(int[][] buildings) 
    {
        BuildingPoint[] buildingPoints = new BuildingPoint[buildings.length * 2];
        int index = 0;
        
        for (int[] building : buildings) 
        {
            buildingPoints[index] = new BuildingPoint();
            buildingPoints[index].x = building[0];
            buildingPoints[index].isStart = true;
            buildingPoints[index].height = building[2];

            buildingPoints[index + 1] = new BuildingPoint();
            buildingPoints[index + 1].x = building[1];
            buildingPoints[index + 1].isStart = false;
            buildingPoints[index + 1].height = building[2];
            
            index += 2;
        }
        
        Arrays.sort(buildingPoints);

        TreeMap<Integer, Integer> queue = new TreeMap<>();
        queue.put(0, 1);
        
        int prevMaxHeight = 0;
        List<int[]> result = new ArrayList<>();
        
        for (BuildingPoint buildingPoint : buildingPoints) 
        {
            // If it is the start of a building, increment the height tracking frequency
            if (buildingPoint.isStart) 
            {
                queue.compute(buildingPoint.height, (key, value) -> {
                    if (value != null) 
                    {
                        return value + 1;
                    }
                    return 1;
                });
            } 
            // If it is the end of a building, decrement or remove the height tracking frequency
            else 
            {
                queue.compute(buildingPoint.height, (key, value) -> {
                    if (value == 1) 
                    {
                        return null;
                    }
                    return value - 1;
                });
            }
            
            int currentMaxHeight = queue.lastKey();
            
            if (prevMaxHeight != currentMaxHeight) 
            {
                result.add(new int[]{buildingPoint.x, currentMaxHeight});
                prevMaxHeight = currentMaxHeight;
            }
        }
        
        return result;
    }

    public static void main(String args[]) 
    {
        int [][] buildings = {{1,3,4},{3,4,4},{2,6,2},{8,11,4}, {7,9,3},{10,11,2}};
        Skyline sd = new Skyline();
        List<int[]> criticalPoints = sd.getSkyline(buildings);
        criticalPoints.forEach(cp -> System.out.println(cp[0] + " " + cp[1]));

    }
}
