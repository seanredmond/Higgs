/* Author:

*/

$(document).ready(function () {
    function ajaxError(request, type, errorThrown)
    {
        var message = "There was an error with the AJAX request.\n";
        switch (type) {
            case 'timeout':
                message += "The request timed out.";
                break;
            case 'notmodified':
                message += "The request was not modified but was not retrieved from the cache.";
                break;
            case 'parseerror':
                message += "XML/Json format is bad.";
                break;
            default:
                message += "HTTP Error (" + request.status + " " + request.statusText + ").";
        }
        message += "\n";
        alert(message);
    }

    $('#add_field').click(function () {
        $('#next_field').load('./snippets/add-field.php').error(function(data, status) { alert(status); });
        //.complete(function() { alert("complete"); });
        return false;
    });
});





