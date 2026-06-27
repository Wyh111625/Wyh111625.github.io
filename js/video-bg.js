(function() {
    'use strict';

    var VIDEO_CONTAINER_ID = 'video-bg-container';
    var VIDEO_ID = 'video-background';

    function playVideo(video) {
        var playPromise = video.play();

        if (playPromise && typeof playPromise.catch === 'function') {
            playPromise.catch(function() {
                // Some browsers delay autoplay until the first user interaction.
            });
        }
    }

    function initVideoBg() {
        if (document.getElementById(VIDEO_CONTAINER_ID)) return;

        var videoContainer = document.createElement('div');
        videoContainer.id = VIDEO_CONTAINER_ID;

        var video = document.createElement('video');
        video.id = VIDEO_ID;
        video.autoplay = true;
        video.loop = true;
        video.muted = true;
        video.defaultMuted = true;
        video.playsInline = true;
        video.preload = 'auto';
        video.setAttribute('muted', '');
        video.setAttribute('playsinline', '');
        video.setAttribute('webkit-playsinline', '');
        video.setAttribute('aria-hidden', 'true');

        var source = document.createElement('source');
        source.src = '/videos/background.mp4';
        source.type = 'video/mp4';

        video.appendChild(source);
        videoContainer.appendChild(video);
        document.body.insertBefore(videoContainer, document.body.firstChild);

        video.addEventListener('canplay', function() {
            playVideo(video);
        }, { once: true });

        playVideo(video);
    }

    if (document.readyState === 'loading') {
        document.addEventListener('DOMContentLoaded', initVideoBg, { once: true });
    } else {
        initVideoBg();
    }
})();
