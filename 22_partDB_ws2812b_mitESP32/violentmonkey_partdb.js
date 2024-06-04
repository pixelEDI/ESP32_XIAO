// ==UserScript==
// @name        PartDB ID Finder
// @namespace   Violentmonkey Scripts
// @match       https://myparts.ipv64.net/*
// @grant       none
// @version     1.0
// @author      pixelEDI
// @description super tolle Descirption und so wichtig
// ==/UserScript==

(function() {
    'use strict';

 var floatEndElements = document.querySelectorAll(".float-end");
     if (floatEndElements.length > 0) {
        //first element with class "float-end"
        let content = floatEndElements[0].textContent;
        content = content.split(":");
        content = content[1].trim();
        content = parseInt(content, 10);

        const url = 'https://nodered.ipv64.net/inventoryid?getID='+content;

        fetch(url)
            .then(response => {
                if (!response.ok) {
                    throw new Error('Network response was not ok');
                }
                return response.text();
            })
            .then(data => {
                console.log('GET-Anfrage erfolgreich gesendet:', data);
            })
            .catch(error => {
                console.error('Fehler beim Senden der GET-Anfrage:', error);
            });

     }

})();
