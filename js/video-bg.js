(function() {
    'use strict';

    var VIDEO_CONTAINER_ID = 'video-bg-container';

    function initVideoBg() {
        if (document.getElementById(VIDEO_CONTAINER_ID)) return;

        var videoContainer = document.createElement('div');
        videoContainer.id = VIDEO_CONTAINER_ID;
        videoContainer.setAttribute('aria-hidden', 'true');
        document.body.insertBefore(videoContainer, document.body.firstChild);
    }

    if (document.readyState === 'loading') {
        document.addEventListener('DOMContentLoaded', initVideoBg, { once: true });
    } else {
        initVideoBg();
    }
})();
