(function($) {
	
	$(document).ready(function(e) {
		
		//$('.action-checkbox').show();
		//$('#SectionNavActionMenu').show();
		
		var actionTotal = 0;
		
		$('a.action-disabled').click(function(e){
			e.preventDefault();
		});
    
		$('input.action-checkbox').change(function() {
			if ($(this).attr('checked')) {
				$(this).siblings().addClass('action-disabled');
				actionTotal++;
			} else {
				$(this).siblings().removeClass('action-disabled');
				actionTotal--;
			}
			$('span#action-total').html(actionTotal);
		});
    
		$('input#action-select-all').change(function() {
			var allChecked = $('input#action-select-all').attr('checked');
			$('input.action-checkbox').each(function() {
				$(this).attr('checked', allChecked);
				if (allChecked) {
					$(this).siblings().addClass('action-disabled');
				} else {
					$(this).siblings().removeClass('action-disabled');
				}
			});
			if (allChecked) {
				$('label#label-action-select-all').text('Deselect All');
				actionTotal = $('input.action-checkbox').length;
			} else {
				$('label#label-action-select-all').text('Select All');
				actionTotal = 0;
			}
			$('span#action-total').html(actionTotal);
		});
		
		var fixedElementTopPosition = $('.fixed-element').offset().top;

		$(window).scroll(function(e){ 
			$el = $('.fixed-element');
			if ($(this).scrollTop() >= fixedElementTopPosition && $el.css('position') != 'fixed'){ 
				$('.fixed-element').css({'position': 'fixed', 'top': '0px'}); 
			}
			if ($(this).scrollTop() < fixedElementTopPosition && $el.css('position') == 'fixed') {
				$('.fixed-element').css({'position': 'static', 'top': fixedElementTopPosition + 'px'});
			}
		});

		var pluralize = '';

		$('#SectionNavActionMenu a#action-delete-selected').click(function() {
				var itemsTotal = $('span#action-total').text();
				if (itemsTotal != 1) {
					pluralize = 's';
				}
				var msg = 'Are you sure you wish to delete ' + itemsTotal + ' selected item' + pluralize + '?';
				if (confirm(msg)) {
					//document.getElementById('action').value = '11';
					//document.forms['form1'].getElementById('action').value = '11';
					document.forms['form1'].action = 'issues.php?action=11';
					document.forms['form1'].submit();
				}
				return false;
		});

		$('#SectionNavActionMenu a#action-complete-ontime-selected').click(function() {
				var itemsTotal = $('span#action-total').text();
				if (itemsTotal != 1) {
					pluralize = 's';
				}
				var msg = 'Are you sure you wish to complete (on time) ' + itemsTotal + ' selected item' + pluralize + '?';
				if (confirm(msg)) {
					document.forms['form1'].getElementById('action').value = '15';
					document.forms['form1'].action = 'issues.php';
					document.forms['form1'].submit();
				}
				return false;
		});

		$('#SectionNavActionMenu a#action-complete-late-selected').click(function() {
				var itemsTotal = $('span#action-total').text();
				if (itemsTotal != 1) {
					pluralize = 's';
				}
				var msg = 'Are you sure you wish to complete (late) ' + itemsTotal + ' selected item' + pluralize + '?';
				if (confirm(msg)) {
					document.forms['form1'].getElementById('action').value = '15';
					document.forms['form1'].action = 'issues.php';
					document.forms['form1'].submit();
				}
				return false;
		});
		
  });
	
})(jQuery);