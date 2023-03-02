export default () => {
    const observer = new IntersectionObserver((entries) => {
        entries.forEach((entry) => {
            if (entry.isIntersecting) {
                entry.target.classList.add('visible');
                observer.unobserve(entry.target);
            }
        });
    });

    globalThis.setupCardFlyin = (card) => {
        if (card === undefined || card === null)
            return;

        observer.observe(card);
    }
};