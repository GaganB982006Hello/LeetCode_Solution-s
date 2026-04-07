/*
A width x height grid is on an XY-plane with the bottom-left cell at (0, 0) and the top-right cell at (width - 1, height - 1). The grid is aligned with the four cardinal directions ("North", "East", "South", and "West"). A robot is initially at cell (0, 0) facing direction "East".

The robot can be instructed to move for a specific number of steps. For each step, it does the following.

Attempts to move forward one cell in the direction it is facing.
If the cell the robot is moving to is out of bounds, the robot instead turns 90 degrees counterclockwise and retries the step.
After the robot finishes moving the number of steps required, it stops and awaits the next instruction.

Implement the Robot class:

Robot(int width, int height) Initializes the width x height grid with the robot at (0, 0) facing "East".
void step(int num) Instructs the robot to move forward num steps.
int[] getPos() Returns the current cell the robot is at, as an array of length 2, [x, y].
String getDir() Returns the current direction of the robot, "North", "East", "South", or "West".
Input
["Robot", "step", "step", "getPos", "getDir", "step", "step", "step", "getPos", "getDir"]
[[6, 3], [2], [2], [], [], [2], [1], [4], [], []]
Output
[null, null, null, [4, 0], "East", null, null, null, [1, 2], "West"]

Explanation
Robot robot = new Robot(6, 3); // Initialize the grid and the robot at (0, 0) facing East.
robot.step(2);  // It moves two steps East to (2, 0), and faces East.
robot.step(2);  // It moves two steps East to (4, 0), and faces East.
robot.getPos(); // return [4, 0]
robot.getDir(); // return "East"
robot.step(2);  // It moves one step East to (5, 0), and faces East.
                // Moving the next step East would be out of bounds, so it turns and faces North.
                // Then, it moves one step North to (5, 1), and faces North.
robot.step(1);  // It moves one step North to (5, 2), and faces North (not West).
robot.step(4);  // Moving the next step North would be out of bounds, so it turns and faces West.
                // Then, it moves four steps West to (1, 2), and faces West.
robot.getPos(); // return [1, 2]
robot.getDir(); // return "West"

 

Constraints:

2 <= width, height <= 100
1 <= num <= 105
At most 104 calls in total will be made to step, getPos, and getDir.
*/

typedef struct {
    int w, h, perimeter, pos;
    bool moved;
} Robot;

Robot* robotCreate(int width, int height) {
    Robot* obj = (Robot*)malloc(sizeof(Robot));
    obj->w = width;
    obj->h = height;
    obj->perimeter = 2 * (width + height) - 4;
    obj->pos = 0;
    obj->moved = false;
    return obj;
}

void robotStep(Robot* obj, int num) {
    obj->moved = true;
    obj->pos = (obj->pos + num) % obj->perimeter;
}

int* robotGetPos(Robot* obj, int* retSize) {
    *retSize = 2;
    int* res = (int*)malloc(2 * sizeof(int));
    int p = obj->pos;
    if (p < obj->w) { res[0] = p; res[1] = 0; }
    else if (p < obj->w + obj->h - 1) { res[0] = obj->w - 1; res[1] = p - (obj->w - 1); }
    else if (p < 2 * obj->w + obj->h - 2) { res[0] = obj->w - 1 - (p - (obj->w + obj->h - 2)); res[1] = obj->h - 1; }
    else { res[0] = 0; res[1] = obj->h - 1 - (p - (2 * obj->w + obj->h - 3)); }
    return res;
}

char* robotGetDir(Robot* obj) {
    if (!obj->moved) return "East";
    int p = obj->pos;
    if (p > 0 && p < obj->w) return "East";
    if (p >= obj->w && p < obj->w + obj->h - 1) return "North";
    if (p >= obj->w + obj->h - 1 && p < 2 * obj->w + obj->h - 2) return "West";
    return "South";
}

void robotFree(Robot* obj) {
    free(obj);
}
