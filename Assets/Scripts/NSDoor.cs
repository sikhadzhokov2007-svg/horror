using UnityEngine;

namespace NightShift
{
    /// <summary>Simple interactable door used by the runtime school blockout.</summary>
    public sealed class NSDoor : MonoBehaviour
    {
        [SerializeField] private float openAngle = 90f;
        [SerializeField] private float rotationSpeed = 180f;

        private bool isOpen;
        private Quaternion closedRotation;
        private Quaternion openRotation;
        private Collider doorCollider;

        private void Awake()
        {
            closedRotation = transform.rotation;
            openRotation = closedRotation * Quaternion.Euler(0f, openAngle, 0f);
            doorCollider = GetComponent<Collider>();
        }

        private void Update()
        {
            Quaternion target = isOpen ? openRotation : closedRotation;
            transform.rotation = Quaternion.RotateTowards(transform.rotation, target, rotationSpeed * Time.deltaTime);
        }

        public void Toggle()
        {
            isOpen = !isOpen;
            if (doorCollider != null)
                doorCollider.enabled = !isOpen;
        }
    }
}
