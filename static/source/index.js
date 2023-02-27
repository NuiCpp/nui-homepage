import setupCardFlyin from './card_flyin';

import {
    Navbar as Navbar,
    Button as Button
} from 'bootstrap';

import { EditorState, Compartment } from '@codemirror/state';
import { cpp } from '@codemirror/lang-cpp';
import { EditorView, basicSetup } from 'codemirror';

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
})()