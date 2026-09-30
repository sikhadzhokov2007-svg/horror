using UnityEngine;

namespace NightShift
{
    /// <summary>Creates the first playable school entrance, corridor and classrooms at runtime.</summary>
    public sealed class NSSchoolBlockout : MonoBehaviour
    {
        private readonly Color floorColor = new Color(0.08f, 0.09f, 0.12f);
        private readonly Color wallColor = new Color(0.04f, 0.05f, 0.07f);

        public void Build()
        {
            AddBlock("Entrance floor", new Vector3(0f, -0.1f, 0f), new Vector3(60f, 0.2f, 40f), floorColor);
            AddBlock("Corridor floor", new Vector3(52f, -0.1f, 0f), new Vector3(50f, 0.2f, 10f), floorColor);
            AddBlock("Classroom wing floor", new Vector3(104f, -0.1f, 0f), new Vector3(24f, 0.2f, 40f), floorColor);
            AddBlock("Corridor ceiling", new Vector3(52f, 4.5f, 0f), new Vector3(60f, 0.2f, 12f), wallColor);

            for (float x = 0f; x <= 104f; x += 4f)
            {
                AddBlock("Left wall", new Vector3(x, 2.25f, -5.2f), new Vector3(0.2f, 4.5f, 0.2f), wallColor);
                AddBlock("Right wall", new Vector3(x, 2.25f, 5.2f), new Vector3(0.2f, 4.5f, 0.2f), wallColor);
            }

            for (int room = 0; room < 3; room++)
            {
                float x = 76f + room * 12f;
                AddBlock("Classroom floor", new Vector3(x, -0.1f, 11.5f), new Vector3(10f, 0.2f, 13f), new Color(0.12f, 0.10f, 0.08f));
                AddBlock("Classroom back wall", new Vector3(x, 2.25f, 18f), new Vector3(10f, 4.5f, 0.2f), wallColor);
                AddBlock("Classroom left wall", new Vector3(x - 5f, 2.25f, 11.5f), new Vector3(0.2f, 4.5f, 13f), wallColor);
                AddBlock("Classroom right wall", new Vector3(x + 5f, 2.25f, 11.5f), new Vector3(0.2f, 4.5f, 13f), wallColor);
                CreateDoor(new Vector3(x, 1.25f, 5.4f));
            }
        }

        private static void AddBlock(string blockName, Vector3 position, Vector3 scale, Color color)
        {
            GameObject block = GameObject.CreatePrimitive(PrimitiveType.Cube);
            block.name = blockName;
            block.transform.SetPositionAndRotation(position, Quaternion.identity);
            block.transform.localScale = scale;
            block.GetComponent<Renderer>().material.color = color;
        }

        private static void CreateDoor(Vector3 position)
        {
            GameObject door = GameObject.CreatePrimitive(PrimitiveType.Cube);
            door.name = "Interactable classroom door";
            door.transform.position = position;
            door.transform.localScale = new Vector3(0.15f, 2.5f, 1.5f);
            door.GetComponent<Renderer>().material.color = new Color(0.12f, 0.2f, 0.32f);
            door.AddComponent<NSDoor>();
        }
    }
}
