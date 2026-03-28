import setupCardFlyin from './card_flyin';

import {
    Navbar as Navbar,
    Button as Button
} from 'bootstrap';

import { EditorState, Compartment } from '@codemirror/state';
import { cpp } from '@codemirror/lang-cpp';
import { EditorView, basicSetup } from 'codemirror';
import { dark } from './codemirror_theme';

(() => {
    globalThis.createCodeMirror = (parent, initialText, readonly) => {
        let tabSize = new Compartment();
        let readOnly = new Compartment();
        let lang = new Compartment();

        if (initialText === undefined)
            initialText = '';

        if (typeof parent === 'string')
            parent = document.getElementById(parent);

        if (readonly === undefined)
            readonly = false;

        const state = EditorState.create({
            extensions: [
                basicSetup,
                cpp(),
                dark,
                //lang.of(EditorState.languageData.of(cpp())),
                tabSize.of(EditorState.tabSize.of(4)),
                readOnly.of(EditorState.readOnly.of(readonly))
            ],
            doc: initialText
        });

        const editor = new EditorView({
            state,
            parent
        });

        return editor;
    }

    setupCardFlyin();

    document.addEventListener('mousedown', (e) => {
        const resizer = e.target.closest('.example__resizer');
        if (!resizer) return;

        const body = resizer.parentElement;
        const editorSection = resizer.previousElementSibling;

        const startX = e.clientX;
        const startEditorWidth = editorSection.getBoundingClientRect().width;

        resizer.classList.add('example__resizer--active');
        document.body.style.cursor = 'col-resize';
        document.body.style.userSelect = 'none';

        const onMouseMove = (e) => {
            const delta = e.clientX - startX;
            const bodyWidth = body.getBoundingClientRect().width;
            const resizerMargin = parseFloat(getComputedStyle(resizer).marginLeft) * 2;
            const newWidth = Math.max(150, Math.min(startEditorWidth + delta, bodyWidth - resizer.offsetWidth - resizerMargin - 150));
            editorSection.style.flex = 'none';
            editorSection.style.width = newWidth + 'px';
        };

        const onMouseUp = () => {
            resizer.classList.remove('example__resizer--active');
            document.body.style.cursor = '';
            document.body.style.userSelect = '';
            document.removeEventListener('mousemove', onMouseMove);
            document.removeEventListener('mouseup', onMouseUp);
        };

        document.addEventListener('mousemove', onMouseMove);
        document.addEventListener('mouseup', onMouseUp);
        e.preventDefault();
    });
})()