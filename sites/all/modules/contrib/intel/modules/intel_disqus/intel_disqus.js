(function ($) {

/**
 * Provide the summary information for the block settings vertical tabs.
 */
Drupal.behaviors.intel_disqus = {
  attach: function (context) {
	_l10iq.push(['addCallback', 'saveCommentSubmitPostSubmit', this.saveCommentSubmitPostCallbackSubmit, this]);
  },

  saveCommentSubmitPostCallbackSubmit: function (data) {
    if (data.type != 'disqus') {
      return;
    }
    var data = {
      vtk: _ioq.vtk,
      commentid: data.commentid
    };
    var url = ('https:' == document.location.protocol) ? 'https://' : 'http://';
    url += Drupal.settings.intel.config.cmsHostpath + "intel_disqus/comment_submit_js";
      var params = {
          dataType: 'json',
          url: url,
          data: data,
          type: 'GET'
      };
    jQuery.ajax(params);
  }
};

})(jQuery);