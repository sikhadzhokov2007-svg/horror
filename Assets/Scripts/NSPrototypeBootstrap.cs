using UnityEngine;
using UnityEngine.SceneManagement;

namespace NightShift
{
    /// <summary>Runs in an empty Unity scene and creates the prototype automatically.</summary>
    public static class NSPrototypeBootstrap
    {
        [RuntimeInitializeOnLoadMethod(RuntimeInitializeLoadType.AfterSceneLoad)]
        private static void CreatePrototype()
        {
            if (Object.FindFirstObjectByType<NSFirstPersonController>() != null)
                return;

            RenderSettings.ambientLight = new Color(0.015f, 0.02f, 0.04f);
            CreateLighting();
            CreatePlayer();

            GameObject school = new GameObject("Night Shift school blockout");
            school.AddComponent<NSSchoolBlockout>().Build();
        }

        private static void CreatePlayer()
        {
            GameObject player = new GameObject("Player");
            player.transform.position = new Vector3(0f, 0.02f, 0f);
            CharacterController controller = player.AddComponent<CharacterController>();
            controller.height = 1.8f;
            controller.radius = 0.35f;
            controller.center = new Vector3(0f, 0.9f, 0f);

            GameObject cameraObject = new GameObject("First person camera");
            cameraObject.transform.SetParent(player.transform);
            cameraObject.transform.localPosition = new Vector3(0f, 1.62f, 0f);
            cameraObject.AddComponent<Camera>();
            cameraObject.AddComponent<AudioListener>();
            player.AddComponent<NSFirstPersonController>();
        }

        private static void CreateLighting()
        {
            GameObject moon = new GameObject("Moonlight");
            Light moonLight = moon.AddComponent<Light>();
            moonLight.type = LightType.Directional;
            moonLight.color = new Color(0.35f, 0.5f, 1f);
            moonLight.intensity = 0.35f;
            moon.transform.rotation = Quaternion.Euler(45f, -30f, 0f);

            GameObject entranceLight = new GameObject("Flickering entrance light");
            entranceLight.transform.position = new Vector3(4f, 3.8f, 0f);
            Light pointLight = entranceLight.AddComponent<Light>();
            pointLight.type = LightType.Point;
            pointLight.color = new Color(0.55f, 0.7f, 1f);
            pointLight.range = 16f;
            pointLight.intensity = 2f;
        }
    }
}
