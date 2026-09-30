using UnityEngine;

namespace NightShift
{
    [RequireComponent(typeof(CharacterController))]
    public sealed class NSFirstPersonController : MonoBehaviour
    {
        [SerializeField] private float walkSpeed = 3.2f;
        [SerializeField] private float sprintSpeed = 5.4f;
        [SerializeField] private float crouchSpeed = 1.7f;
        [SerializeField] private float gravity = -20f;
        [SerializeField] private float interactionDistance = 2.5f;

        private CharacterController controller;
        private Camera playerCamera;
        private float verticalVelocity;
        private float pitch;
        private float standingHeight;

        private void Awake()
        {
            controller = GetComponent<CharacterController>();
            playerCamera = GetComponentInChildren<Camera>();
            standingHeight = controller.height;
            Cursor.lockState = CursorLockMode.Locked;
            Cursor.visible = false;
        }

        private void Update()
        {
            Look();
            Move();
            if (Input.GetKeyDown(KeyCode.E))
                Interact();
        }

        private void Look()
        {
            transform.Rotate(Vector3.up * Input.GetAxisRaw("Mouse X") * 2.5f);
            pitch = Mathf.Clamp(pitch - Input.GetAxisRaw("Mouse Y") * 2.5f, -85f, 85f);
            playerCamera.transform.localRotation = Quaternion.Euler(pitch, 0f, 0f);
        }

        private void Move()
        {
            bool crouching = Input.GetKey(KeyCode.LeftControl);
            controller.height = crouching ? standingHeight * 0.6f : standingHeight;
            controller.center = new Vector3(0f, controller.height * 0.5f, 0f);

            float speed = crouching ? crouchSpeed : (Input.GetKey(KeyCode.LeftShift) ? sprintSpeed : walkSpeed);
            Vector3 input = new Vector3(Input.GetAxisRaw("Horizontal"), 0f, Input.GetAxisRaw("Vertical"));
            Vector3 horizontal = transform.TransformDirection(Vector3.ClampMagnitude(input, 1f)) * speed;

            if (controller.isGrounded && verticalVelocity < 0f)
                verticalVelocity = -2f;
            if (controller.isGrounded && Input.GetKeyDown(KeyCode.Space))
                verticalVelocity = 6f;

            verticalVelocity += gravity * Time.deltaTime;
            controller.Move((horizontal + Vector3.up * verticalVelocity) * Time.deltaTime);
        }

        private void Interact()
        {
            Ray ray = new Ray(playerCamera.transform.position, playerCamera.transform.forward);
            if (Physics.Raycast(ray, out RaycastHit hit, interactionDistance))
            {
                NSDoor door = hit.collider.GetComponentInParent<NSDoor>();
                if (door != null)
                    door.Toggle();
            }
        }
    }
}
